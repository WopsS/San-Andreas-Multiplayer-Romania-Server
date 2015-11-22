#pragma once

class Point
{
public:

	Point(float X) : X(X) { };
	~Point() { };

	inline bool operator==(float PointX)
	{
		return X == PointX;
	}

	inline bool operator==(const Point& Point)
	{
		return X == Point.X;
	}

	float X;
};

class Point2D
{
public:

	Point2D(float X, float Y) : X(X), Y(Y) { };
	~Point2D() { };

	inline bool operator==(const Point2D& Point)
	{
		return X == Point.X && Y == Point.Y;
	}

	float X;
	float Y;
};

class Point3D
{
public:

	Point3D(float X, float Y, float Z) : X(X), Y(Y), Z(Z) { };
	~Point3D() { };

	inline bool operator==(const Point3D& Point)
	{
		return X == Point.X && Y == Point.Y && Z == Point.Z;
	}

	float X;
	float Y;
	float Z;
};