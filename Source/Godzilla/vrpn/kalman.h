// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class GODZILLA_API Kalman
{
public:
	int isEnabled; /**< If set to 0, disable kalman filter */

	double xk_prev[3]; /**< Filtered position, velocity, and acceleration */
	long time_prev;    /**< Time of previous measurement in milliseconds */

	double p[9];   /**< Estimated error of our current state */
	double qScale; /**< Scaling factor for Q matrix (system error) */
	double r;      /**< Variance of measurement error */
	double h[3];   /**< Measurement matrix (converts measurement into state) */
	double a[9];   /**< Transition matrix (moves state forward one step) */

	Kalman(float sigma_meas, float qScale);
	float estimate(float measured);

	~Kalman();

private:
#ifdef _WIN32
	typedef struct timeval {
		long tv_sec;
		long tv_usec;
	} timeval;

#endif
	long getMilleTime();
};
