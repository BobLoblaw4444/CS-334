#pragma once

#include <math.h>

template <class VECTOR_T>
class MyVector
{
	public:
		VECTOR_T components[4];

		MyVector<VECTOR_T>();
		MyVector<VECTOR_T>(VECTOR_T x, VECTOR_T y, VECTOR_T z);
		MyVector(VECTOR_T x, VECTOR_T y, VECTOR_T z, VECTOR_T w);

		void Normalize();
		VECTOR_T Length();
		VECTOR_T DotProduct(MyVector<VECTOR_T> vector2);
		VECTOR_T MatrixDotProduct(MyVector<VECTOR_T> vector2);
		MyVector<VECTOR_T> CrossProduct(MyVector<VECTOR_T> vector2);

		VECTOR_T& operator[](int index);
		void operator*(VECTOR_T scalar);
		void operator/(VECTOR_T scalar);
		MyVector<VECTOR_T> operator+ (MyVector<VECTOR_T> vector2);
		MyVector<VECTOR_T> operator- (MyVector<VECTOR_T> vector2);		
};

// Default Constructor
template <class VECTOR_T>
MyVector<VECTOR_T>::MyVector()
{
		components[0] = 0;
		components[1] = 0;
		components[2] = 0;
		components[3] = 1;
}

template <class VECTOR_T>
MyVector<VECTOR_T>::MyVector(VECTOR_T x, VECTOR_T y, VECTOR_T z)
{
		components[0] = x;
		components[1] = y;
		components[2] = z;
		components[3] = 1;
}

template <class VECTOR_T>
MyVector<VECTOR_T>::MyVector(VECTOR_T x, VECTOR_T y, VECTOR_T z, VECTOR_T w)
{
		components[0] = x;
		components[1] = y;
		components[2] = z;
		components[3] = w;
}

template <class VECTOR_T>
void MyVector<VECTOR_T>::Normalize()
{
	float length = Length();

	components[0] /= length;
	components[1] /= length;
	components[2] /= length;
}

template <class VECTOR_T>
VECTOR_T MyVector<VECTOR_T>::Length()
{
	VECTOR_T length = 0;
	for (int i = 0; i < 3; i++)
	{
		length += pow(components[i], 2);
	}
	
	return sqrt(length);
}

template <class VECTOR_T>
VECTOR_T MyVector<VECTOR_T>::DotProduct(MyVector<VECTOR_T> vector2)
{
	return ((components[0] * vector2.components[0]) + (components[1] * vector2.components[1]) + (components[2] * vector2.components[2]));
}

// Dot product using 4 components to aid with matrix multiplication
template <class VECTOR_T>
VECTOR_T MyVector<VECTOR_T>::MatrixDotProduct(MyVector<VECTOR_T> vector2)
{
	return ((components[0] * vector2.components[0]) + (components[1] * vector2.components[1]) + (components[2] * vector2.components[2]) + (components[3] * vector2.components[3]));
}

template <class VECTOR_T>
MyVector<VECTOR_T> MyVector<VECTOR_T>::CrossProduct(MyVector<VECTOR_T> vector2)
{
	VECTOR_T x = (components[1] * vector2.components[2]) - (components[2] * vector2.components[1]);
	VECTOR_T y = -((components[0] * vector2.components[2]) - (components[2] * vector2.components[0]));
	VECTOR_T z = (components[0] * vector2.components[1]) - (components[1] * vector2.components[0]);

	return MyVector<VECTOR_T>(x,y,z);
}

// Operators

template <class VECTOR_T>
VECTOR_T& MyVector<VECTOR_T>::operator[] (int index)
{
	return components[index];
}

template <class VECTOR_T>
void MyVector<VECTOR_T>::operator* (VECTOR_T scalar)
{
	components[0] *= scalar;
	components[1] *= scalar;
	components[2] *= scalar;
}

template <class VECTOR_T>
void MyVector<VECTOR_T>::operator/ (VECTOR_T scalar)
{
	components[0] /= scalar;
	components[1] /= scalar;
	components[2] /= scalar;
}

template <class VECTOR_T>
MyVector<VECTOR_T> MyVector<VECTOR_T>::operator+ (MyVector<VECTOR_T> vector2)
{
	VECTOR_T x = components[0] + vector2.components[0];
	VECTOR_T y = components[1] + vector2.components[1];
	VECTOR_T z = components[2] + vector2.components[2];

	return MyVector<VECTOR_T>(x,y,z);
}

template <class VECTOR_T>
MyVector<VECTOR_T> MyVector<VECTOR_T>::operator- (MyVector<VECTOR_T> vector2)
{
	VECTOR_T x = components[0] - vector2.components[0];
	VECTOR_T y = components[1] - vector2.components[1];
	VECTOR_T z = components[2] - vector2.components[2];

	return MyVector<VECTOR_T>(x,y,z);
}