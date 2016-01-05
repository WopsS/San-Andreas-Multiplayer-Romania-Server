#pragma once

template<typename T>
class Point
{
public:

	Point() = default;
	Point(const T X) : X(X) { };
	~Point() = default;

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

	Point2D() = default;
	Point2D(const T X, const T Y) : X(X), Y(Y) { };
	~Point2D() = default;

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

	Point3D() = default;
	Point3D(const T X, const T Y, const T Z) : X(X), Y(Y), Z(Z) { };
	~Point3D() = default;

	inline bool operator==(const Point3D& Point)
	{
		return X == Point.X && Y == Point.Y && Z == Point.Z;
	}

	T X;
	T Y;
	T Z;
};