#pragma once

template<typename T>
class Point
{
public:

	Point() { };
	Point(const T X) : X(X) { };
	~Point() { };

	inline bool operator==(const T PointX)
	{
		return X == PointX;
	}

	inline bool operator==(const Point& Point)
	{
		return X == Point.X;
	}

	T X;
};

template<typename T>
class Point2D
{
public:

	Point2D() { };
	Point2D(const T X, const T Y) : X(X), Y(Y) { };
	~Point2D() { };

	inline bool operator==(const Point2D& Point)
	{
		return X == Point.X && Y == Point.Y;
	}

	T X;
	T Y;
};

template<typename T>
class Point3D
{
public:

	Point3D() { };
	Point3D(const T X, const T Y, const T Z) : X(X), Y(Y), Z(Z) { };
	~Point3D() { };

	inline bool operator==(const Point3D& Point)
	{
		return X == Point.X && Y == Point.Y && Z == Point.Z;
	}

	T X;
	T Y;
	T Z;
};