// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"

#include <string.h>
#include <math.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#include <stdint.h>
#endif

#include "kalman.h"
#include "vecmat.h"


long Kalman::getMilleTime(){
#ifndef _WIN32
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long ms = (tv.tv_sec * 1000L) + tv.tv_usec / 1000L;
#else
	/*static const uint64_t EPOCH = ((uint64_t)116444736000000000ULL);

	SYSTEMTIME  system_time;
	FILETIME    file_time;
	uint64_t    time;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	time = ((uint64_t)file_time.dwLowDateTime);
	time += ((uint64_t)file_time.dwHighDateTime) << 32;*/

	//Note that GetTickCount can be used since we just was to calculate delta time in this file
	long ms = GetTickCount64();//(long)(system_time.wMilliseconds * 1000);
#endif
	return ms;
}

Kalman::Kalman(float sigma_meas, float qScale){
	isEnabled = 1;

	time_prev = getMilleTime();

	float sigma_model = 100; // confidence in current state (smaller=more confident)

	/* kalman_estimate() creates a Q matrix appropriate for a model
	where we are handling position, velocity, and
	acceleration. However, we can scale this matrix to indicate how
	confident we are in our model. Setting it to 0 indicates a
	belief that our model is perfect. Making this value will cause
	the filter to better track large jumps in data.

	In the case of a tracking, the user's movements is noise because they
	will be moving in complex and unpredictable ways which will not fit our
	model.  If we are assuming position is changing due to velocity and
	velocity is changing due to acceleration, and acceleration is fixed,
	errors in acceleration will occur.
	*/
	qScale = qScale;

	// Variance of our measurements.  A small number indicates that our
	// measurements are noise-free.
	r = sigma_meas * sigma_meas;

	// Confidence in current state (changes as program runs).
	// Smaller numbers = more confidence.
	Matrix::identity(p, 3);
	for (int i = 0; i<9; i++)
		p[i] = p[i] * sigma_model;

	// Guess for initial state (position, velocity, acceleration)
	Vector::set(xk_prev, 0, 0, 0);

	// Converts our state into the set of variables we are measuring.
	Vector::set(h, 1, 0, 0);
}

Kalman::~Kalman(){}

float Kalman::estimate(float measured){
	if (isEnabled == 0)
		return measured;

	long now = getMilleTime();
	double dt = (now - time_prev) / 1000.0;

	/* A is the transition matrix which will move our state ahead by
	* one timestep. */
	{
		double row1[3] = { 1, dt, .5*dt*dt };
		double row2[3] = { 0, 1, dt };
		double row3[3] = { 0, 0, 1 };
		Matrix::setRow(a, row1, 0, 3);
		Matrix::setRow(a, row2, 1, 3);
		Matrix::setRow(a, row3, 2, 3);
	}
	// mat3d_print(a);


	/* Q is the process/system noise covariance.

	From pg 156 of "Fundamentals of Kalman filtering: a practical
	approach" which provides tables where each state is a
	derivative of the one above it and all of the noise enters into
	the bottom-most state.  The resulting matrix can be scaled by a
	scalar as needed (called the "continuous process-noise spectral
	density") in the book.
	*/
	double q[9];
	{
		double row1[3] = { pow(dt, 5) / 20, pow(dt, 4) / 8, pow(dt, 3) / 6 };
		double row2[3] = { pow(dt, 4) / 8, pow(dt, 3) / 3, pow(dt, 2) / 2 };
		double row3[3] = { pow(dt, 3) / 6, pow(dt, 2) / 2, dt };
		Matrix::setRow(q, row1, 0, 3);
		Matrix::setRow(q, row2, 1, 3);
		Matrix::setRow(q, row3, 2, 3);
	}
	for (int i = 0; i<9; i++)
		q[i] = q[i] * qScale;
	// mat3d_print(q);

	// === PREDICTION ===

	// Project the state ahead
	// kx_minus = A * xk_prev     (no control input!)
	double xk_minus[3];
	Matrix::mult_vecNd_new(xk_minus, a, xk_prev, 3);

	// Project the error covariance ahead.
	// Pminus = A * P * A^T + Q
	double a_transpose[9];
	Matrix::transpose_new(a_transpose, a);

	double a_dot_p[9];
	Matrix::mult_matNd_new(a_dot_p, a, p, 3);   //  A*P

	double p_minus[9];
	Matrix::mult_matNd_new(p_minus, a_dot_p, a_transpose, 3); // (A*P)*A^T
	for (int i = 0; i<9; i++)                               // add Q
		p_minus[i] = p_minus[i] + q[i];


	// === MEASUREMENT UPDATE or CORRECTION ===
	// Compute the Kalman gain
	// K = Pminus * transpose(H) * (H * Pminus * transpose(H) + R)^-1
	// 
	// Note: H is a column vector, transposing just changes it between
	// a vertical and horizontal matrix. Multiplying a rowVec * colVec
	// is the same as taking a dot product between them.

	// Pminus * transpose(H)
	double pminus_h[3];
	Matrix::mult_vecNd_new(pminus_h, p_minus, h, 3);
	// H * (Pminus*transpose(H)) + R
	double s = Vector::dot(h, pminus_h, 3) + r;
	double inv_s = 1 / (s);
	double k[3];
	Vector::scalarMult_new(k, pminus_h, inv_s, 3);
	//vec3d_print(k); // if k=0, relies 100% on predicted value


	// Update the estimate with the measurement. (Weights the current
	// measurement and our prediction to come up with a new value.)
	// 
	// x = x + K * ( obs - H * x )
	double paren = measured - Vector::dot(h, xk_minus, 3);
	double k_dot_paren[3];
	Vector::scalarMult_new(k_dot_paren, k, paren, 3);
	double xk[3];
	Vector::add_new(xk, xk_minus, k_dot_paren, 3);

	// Update the error covariance
	// P = P - (K * H) * P
	double k_mult_h[9];
	Vector::mult_vecNd(k_mult_h, k, h, 3); // K*H
	double subtrahend[9];
	Matrix::mult_matNd_new(subtrahend, k_mult_h, p_minus, 3);  // (K*H)*P
	for (int i = 0; i<9; i++)
		p[i] = p_minus[i] - subtrahend[i]; // P = P-(K*H)*P

	// vec3d_print(xk); // Print current estimate of pos, velocity, accel
	time_prev = now;
	Vector::copy(xk_prev, xk, 3);
	return xk[0];
}