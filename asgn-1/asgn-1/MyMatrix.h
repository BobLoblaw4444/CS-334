#pragma once

#include "MyPoint.h"
#include "MyVector.h"
#include <math.h>

template <class MATRIX_T>
class MyMatrix
{
	public:
		MATRIX_T components[16];
		MyVector<MATRIX_T> rows[4];
		MyVector<MATRIX_T> columns[4];

		MyMatrix<MATRIX_T>();
		MyMatrix<MATRIX_T>(MATRIX_T val00, MATRIX_T val01, MATRIX_T val02, MATRIX_T val03, 
						   MATRIX_T val10, MATRIX_T val11, MATRIX_T val12, MATRIX_T val13,
						   MATRIX_T val20, MATRIX_T val21, MATRIX_T val22, MATRIX_T val23,
						   MATRIX_T val30, MATRIX_T val31, MATRIX_T val32, MATRIX_T val33);

		MATRIX_T& operator[](int index);
		MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Transpose();

		MyPoint<MATRIX_T> operator*(MyPoint<MATRIX_T> point);
		MyVector<MATRIX_T> operator*(MyVector<MATRIX_T> vector);
		MyMatrix<MATRIX_T> operator*(MyMatrix<MATRIX_T> matrix);

		MyMatrix<MATRIX_T> Rotate(char direction, MATRIX_T angle);
		MyMatrix<MATRIX_T> Translate(MATRIX_T x, MATRIX_T y, MATRIX_T z);
		MyMatrix<MATRIX_T> Scale(MATRIX_T x, MATRIX_T y, MATRIX_T z);
		MyMatrix<MATRIX_T> Identity();

	private:
		void SetRowsAndColumns();
};

template <class MATRIX_T>
MyMatrix<MATRIX_T>::MyMatrix()
{
	components[0] = 1;
	components[1] = 0;
	components[2] = 0;
	components[3] = 0;
	components[4] = 0;
	components[5] = 1;
	components[6] = 0;
	components[7] = 0;
	components[8] = 0;
	components[9] = 0;
	components[10] = 1;
	components[11] = 0;
	components[12] = 0;
	components[13] = 0;
	components[14] = 0;
	components[15] = 1;

	SetRowsAndColumns();
}

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

	SetRowsAndColumns();
}

template <class MATRIX_T>
MATRIX_T& MyMatrix<MATRIX_T>::operator[] (int index)
{
	SetRowsAndColumns();
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
	MATRIX_T newComponents[4];

	for(int i = 0; i < 4; i++)
	{
		newComponents[i] = vector.MatrixDotProduct(rows[i]);
	}

	if(newComponents[3] != 0 && newComponents[3] != 1)
	{
		for(int i = 0; i < 3; i++)
		{
			newComponents[i] /= newComponents[3];
		}
	}

	return MyVector<MATRIX_T>(newComponents[0], newComponents[1], newComponents[2]);
}

template <class MATRIX_T>
MyPoint<MATRIX_T> MyMatrix<MATRIX_T>::operator*(MyPoint<MATRIX_T> point)
{
	MATRIX_T x = (point.components[0] * components[0]) +  (point.components[1] * components[4]) +  (point.components[2] * components[8]) +  (point.components[3] * components[12]);
	MATRIX_T y = (point.components[0] * components[1]) +  (point.components[1] * components[5]) +  (point.components[2] * components[9]) +  (point.components[3] * components[13]);
	MATRIX_T z = (point.components[0] * components[2]) +  (point.components[1] * components[6]) +  (point.components[2] * components[10]) +  (point.components[3] * components[14]);
	MATRIX_T w = (point.components[0] * components[3]) +  (point.components[1] * components[7]) +  (point.components[2] * components[11]) +  (point.components[3] * components[15]);

	if(w != 0 && w != 1)
	{
		x /= w;
		y /= w;
		z /= w;
	}

	return MyPoint<MATRIX_T>(x, y, z);
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::operator*(MyMatrix<MATRIX_T> matrix)
{
	MyMatrix<MATRIX_T> newMatrix(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1);

	int k = 0;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			newMatrix.components[k] = rows[i].MatrixDotProduct(matrix.columns[j]);
			k++;
		}
	}
	return newMatrix.Transpose();
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Rotate(char direction, MATRIX_T angle)
{
	if(direction == 'x' || direction == 'X')
	{
			MyMatrix<MATRIX_T> rotationMatrix(1, 0, 0, 0, 0, cos(-angle), sin(-angle), 0, 0, -sin(-angle), cos(-angle), 0, 0, 0, 0, 1);
			return rotationMatrix;
	}
	else if(direction == 'y' || direction == 'Y')
	{
			MyMatrix<MATRIX_T> rotationMatrix(cos(-angle), 0, -sin(-angle), 0, 0, 1, 0, 0, sin(-angle), 0, cos(-angle), 0, 0, 0, 0, 1);
			return rotationMatrix;
	}
	else if(direction == 'z' || direction == 'Z')
	{
			MyMatrix<MATRIX_T> rotationMatrix(cos(-angle), sin(-angle), 0, 0, -sin(-angle), cos(-angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
			return rotationMatrix;
	}
	return *this;
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Translate(MATRIX_T x, MATRIX_T y, MATRIX_T z)
{
	MyMatrix<MATRIX_T> translationMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1);

	return translationMatrix;
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Scale(MATRIX_T x, MATRIX_T y, MATRIX_T z)
{
	MyMatrix<MATRIX_T> scaleMatrix(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);

	return scaleMatrix;
}

template <class MATRIX_T>
MyMatrix<MATRIX_T> MyMatrix<MATRIX_T>::Identity()
{
	MyMatrix<MATRIX_T> identityMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	return identityMatrix;
}

//Private Methods
template <class MATRIX_T>
void MyMatrix<MATRIX_T>::SetRowsAndColumns()
{
	rows[0] = MyVector<MATRIX_T>(components[0], components[4], components[8], components[12]);
	rows[1] = MyVector<MATRIX_T>(components[1], components[5], components[9], components[13]);
	rows[2] = MyVector<MATRIX_T>(components[2], components[6], components[10], components[14]);
	rows[3] = MyVector<MATRIX_T>(components[3], components[7], components[11], components[15]);

	columns[0] = MyVector<MATRIX_T>(components[0], components[1], components[2], components[3]);
	columns[1] = MyVector<MATRIX_T>(components[4], components[5], components[6], components[7]);
	columns[2] = MyVector<MATRIX_T>(components[8], components[9], components[10], components[11]);
	columns[3] = MyVector<MATRIX_T>(components[12], components[13], components[14], components[15]);
}