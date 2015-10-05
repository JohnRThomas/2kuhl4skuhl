// Fill out your copyright notice in the Description page of Project Settings.

#include "Godzilla.h"
#include "vecmat.h"


void Vector::set(double v[3], double a, double b, double c)
{
	v[0] = a; v[1] = b; v[2] = c;
}

void Vector::copy(double result[], const double a[], const int n)
{
	memcpy(result, a, n*sizeof(double));
}

void Vector::mult_vecNd(double m[], const double A[], const double B[], const int n)
{
	for (int i = 0; i<n; i++){
		for (int j = 0; j<n; j++){
			m[Matrix::getIndex(i, j, n)] = A[i] * B[j];
		}
	}
}
void Vector::scalarMult_new(double result[], const double v[], const double scalar, const int n)
{
	for (int i = 0; i<n; i++)
		result[i] = v[i] * scalar;
}

double Vector::dot(const double A[], const double B[], const int n)
{
	float sum = 0.0f;
	for (int i = 0; i<n; i++)
		sum += A[i] * B[i];
	return sum;
}

void Vector::add_new(double result[], const double a[], const double b[], const int n)
{
	for (int i = 0; i<n; i++)
		result[i] = a[i] + b[i];
}

void Matrix::setRow(double matrix[], const double v[], const int row, const int n)
{
	for (int col = 0; col<n; col++)
		matrix[Matrix::getIndex(row, col, n)] = v[col];
}
void Matrix::identity(double m[], int n)
{
	for (int row = 0; row<n; row++)
		for (int col = 0; col<n; col++)
			if (row == col)
				m[row + col*n] = 1.0;
			else
				m[row + col*n] = 0.0;
}

int Matrix::getIndex(const int row, const int col, const int n)
{
	return row + col*n;
}

void Matrix::mult_vecNd_new(double result[], const double m[], const double v[], const int n)
{
	double tmp[4 * 4]; // avoid using a variable length array
	for (int i = 0; i<n; i++)
	{
		tmp[i] = 0;
		for (int j = 0; j<n; j++)
			tmp[i] += m[Matrix::getIndex(i, j, n)] * v[j];
	}
	Vector::copy(result, tmp, n);
}

void Matrix::transpose(double m[], const int n)
{
	double tmp;
	for (int row = 0; row<n; row++)
	{
		for (int col = 0; col<row; col++)
		{
			int index1 = row + col*n;
			int index2 = col + row*n;
			tmp = m[index1];
			m[index1] = m[index2];
			m[index2] = tmp;
		}
	}
}
void Matrix::copy(double dest[], const double src[], const int n)
{
	memcpy(dest, src, n*n*sizeof(double));
}

void Matrix::transpose_new(double dest[9], const double src[9])
{
	Matrix::copy(dest, src, 3);
	Matrix::transpose(dest, 3);
}

void Matrix::getRow(double result[], const double m[], const int row, const int n)
{
	for (int i = 0; i<n; i++)
		result[i] = m[row + i*n];
}

void Matrix::getColumn(double result[], const double m[], const int col, const int n)
{
	for (int i = 0; i<n; i++)
		result[i] = m[i + col*n];
}

void Matrix::mult_matNd_new(double result[], const double matA[], const double matB[], const int n)
{
	/* Use a temporary matrix so callers can do:
	matrixA = matrixA * matrixB */
	double tempMatrix[4 * 4]; // avoid use of VLAs
	double vecA[4], vecB[4];
	for (int i = 0; i<n; i++)
	{
		/* Get the ith row from matrix a */
		Matrix::getRow(vecA, matA, i, n);
		for (int j = 0; j<n; j++)
		{
			/* Get the jth column from matrix b */
			Matrix::getColumn(vecB, matB, j, n);
			/* Dot product */
			tempMatrix[Matrix::getIndex(i, j, n)] = Vector::dot(vecA, vecB, n);
		}
	}
	Matrix::copy(result, tempMatrix, n);
}