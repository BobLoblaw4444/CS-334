#pragma once

template <class POINT_T>
class MyPoint
{
	public:
		POINT_T components[4];

		MyPoint<POINT_T>();
		MyPoint<POINT_T>(POINT_T x, POINT_T y, POINT_T z);
		POINT_T& operator[](int index);
		MyPoint<POINT_T> operator+ (MyPoint<POINT_T> point2);
		MyPoint<POINT_T> operator- (MyPoint<POINT_T> point2);
};

template <class POINT_T>
MyPoint<POINT_T>::MyPoint()
{
		components[0] = 0;
		components[1] = 0;
		components[2] = 0;
		components[3] = 0;
}

template <class POINT_T>
MyPoint<POINT_T>::MyPoint(POINT_T x, POINT_T y, POINT_T z)
{
		components[0] = x;
		components[1] = y;
		components[2] = z;
		components[3] = 0;
}

template <class POINT_T>
POINT_T& MyPoint<POINT_T>::operator[] (int index)
{
	return components[index];
}

template <class POINT_T>
MyPoint<POINT_T> MyPoint<POINT_T>::operator+ (MyPoint<POINT_T> point2)
{
	POINT_T x = components[0] + point2.components[0];
	POINT_T y = components[1] + point2.components[1];
	POINT_T z = components[2] + point2.components[2];

	return MyPoint(x,y,z);
}

template <class POINT_T>
MyPoint<POINT_T> MyPoint<POINT_T>::operator- (MyPoint<POINT_T> point2)
{
	POINT_T x = components[0] - point2.components[0];
	POINT_T y = components[1] - point2.components[1];
	POINT_T z = components[2] - point2.components[2];

	return MyPoint(x,y,z);
}