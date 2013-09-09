#pragma once

#include "MyVector.h"
#include <math.h>

template <class MATRIX_T>
class MyMatrix
{
	public:
		MATRIX_T components[16];

		MyMatrix<MATRIX_T>(MATRIX_T val00, MATRIX_T val01, MATRIX_T val02, MATRIX_T val03, 
						   MATRIX_T val10, MATRIX_T val11, MATRIX_T val12, MATRIX_T val13,
						   MATRIX_T val20, MATRIX_T val21, MATRIX_T val22, MATRIX_T val23,
						   MATRIX_T val30, MATRIX_T val31, MATRIX_T val32, MATRIX_T val33);

		MATRIX_T& operator[](int index);
		MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Transpose();
		MyVector<MATRIX_T> MyMatrix<MATRIX_T>::operator*(MyVector<MATRIX_T> vector);
};

template <class MATRIX_T>
MyMatrix<MATRIX_T>::MyMatrix(MATRIX_T val00, MATRIX_T val01, MATRIX_T val02, MATRIX_T val03, 
							 MATRIX_T val10, MATRIX_T val11, MATRIX_T val12, MATRIX_T val13,
							 MATRIX_T val20, MATRIX_T val21, MATRIX_T val22, MATRIX_T val23,
							 MATRIX_T val30, MATRIX_T val31, MATRIX_T val32, MATRIX_T val33)
{
	components[0] = val00;
	components[1] = val01;
	components[2] = val02;
	components[3] = val03;
	components[4] = val10;
	components[5] = val11;
	components[6] = val12;
	components[7] = val13;
	components[8] = val20;
	components[9] = val21;
	components[10] = val22;
	components[11] = val23;
	components[12] = val30;
	components[13] = val31;
	components[14] = val32;
	components[15] = val33;
}

template <class MATRIX_T>
MATRIX_T& MyMatrix<MATRIX_T>::operator[] (int index)
{
	return components[index];
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Transpose()
{
	MyMatrix<MATRIX_T> newMatrix(components[0],
								 components[4], 
								 components[8], 
								 components[12],
								 components[1], 
								 components[5],
								 components[9],
								 components[13],
								 components[2], 
								 components[6], 
								 components[10],
								 components[14],
								 components[3],
								 components[7], 
								 components[11],
								 components[15]);

	return newMatrix;
}

template <class MATRIX_T>
MyVector<MATRIX_T> MyMatrix<MATRIX_T>::operator*(MyVector<MATRIX_T> vector)
{

}