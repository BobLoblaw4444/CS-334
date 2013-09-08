#pragma once

#include <stdlib.h>
#include <math.h>

#define NUM_COMPONENTS = 3

template <class VECTOR_T>
class MyVector
{
	public:
		VECTOR_T components[3];

		MyVector<VECTOR_T>(VECTOR_T x, VECTOR_T y, VECTOR_T z);
		VECTOR_T& operator[](int index);
		VECTOR_T length();
};

template <class VECTOR_T>
MyVector<VECTOR_T>::MyVector(VECTOR_T x, VECTOR_T y, VECTOR_T z)
{
		components[0] = x;
		components[1] = y;
		components[2] = z;
}

template <class VECTOR_T>
VECTOR_T& MyVector<VECTOR_T>::operator[] (int index)
{
	return components[index];
}

template <class VECTOR_T>
VECTOR_T MyVector<VECTOR_T>::length()
{
	VECTOR_T length = 0;
	for (int i = 0; i < 3; i++)
	{
		length += pow(components[i], 2);
	}
	
	return sqrt(length);
}