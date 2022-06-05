#pragma once

struct Point2f
{
	Point2f() = default;
	explicit Point2f(float x, float y) : x{ x }, y{ y } {}

	float x, y;
};

struct Point3f
{
	Point3f() = default;
	explicit Point3f(float x, float y, float z) : x{ x }, y{ y }, z{z} {}

	float x, y, z;
};

struct Rectf
{
	Rectf() = default;
	explicit Rectf(float left, float top, float width, float height) : left{ left }, top{ top }, width{ width }, height{ height } {}

	float left, top, width, height;
};
