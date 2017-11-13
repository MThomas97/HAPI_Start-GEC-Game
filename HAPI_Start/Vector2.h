//2D Vector class
#pragma once
#include <cmath>

class Vector2
{
public:
	float x{ 0 };
	float y{ 0 };

	//Constructors
	Vector2()=default;
	Vector2(float newX, float newY) : x(newX), y(newY){}

	inline Vector2 &operator +(const Vector2 &rhs) const;

	inline Vector2 &operator -(const Vector2 &rhs) const;

	inline Vector2 &operator *(const Vector2 &rhs) const;
	
	inline Vector2 &operator *=(const Vector2 &rhs);

	inline Vector2 &operator +=(const Vector2 &rhs);

	inline Vector2 &operator -=(const Vector2 &rhs);

	float Length() const;

	float LengthSquared() const;

	void NormaliseInPlace();

	float Dot(const Vector2 &other) const;

	float Cross(const Vector2 &other) const;

	float Distance(const Vector2 &rhs) const;

	float DistanceSquared(const Vector2 &rhs) const;

};

