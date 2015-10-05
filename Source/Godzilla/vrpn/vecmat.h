// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class GODZILLA_API Vector
{
public:
	static void set(double v[3], double a, double b, double c);
	static void copy(double result[], const double a[], const int n);
	static void mult_vecNd(double m[], const double A[], const double B[], const int n);
	static void scalarMult_new(double result[], const double v[], const double scalar, const int n);
	static double dot(const double A[], const double B[], const int n);
	static void add_new(double result[], const double a[], const double b[], const int n);

	~Vector();
private:
	Vector();
};

class GODZILLA_API Matrix
{
public:
	static void setRow(double matrix[], const double v[], const int row, const int n);
	static int  getIndex(const int row, const int col, const int n);
	static void identity(double m[], int n);
	static void mult_vecNd_new(double result[], const double m[], const double v[], const int n);
	static void transpose(double m[], const int n);
	static void copy(double dest[], const double src[], const int n);
	static void transpose_new(double dest[9], const double src[9]);
	static void mult_matNd_new(double result[], const double matA[], const double matB[], const int n);
	static void getRow(double result[], const double m[], const int row, const int n);
	static void getColumn(double result[], const double m[], const int col, const int n);

	~Matrix();
private:
	Matrix();
};
