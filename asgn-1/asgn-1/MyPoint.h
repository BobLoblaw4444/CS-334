#pragma once

template <class POINT_T>
class MyPoint
{
	public:
		POINT_T components[3];

		MyPoint<POINT_T>(POINT_T x, POINT_T y, POINT_T z);
		POINT_T& operator[](int index);
};

template <class POINT_T>
MyPoint<POINT_T>::MyPoint(POINT_T x, POINT_T y, POINT_T z)
{
		components[0] = x;
		components[1] = y;
		components[2] = z;
}

template <class POINT_T>
POINT_T& MyPoint<POINT_T>::operator[] (int index)
{
	return components[index];
}