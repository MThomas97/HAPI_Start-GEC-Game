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

	Vector2 operator +(const Vector2 &rhs) const;

	Vector2 operator -(const Vector2 &rhs) const;

	Vector2 operator = (float rhs) { return Vector2(x = rhs, y = rhs); }

	Vector2 operator += (float rhs) { return Vector2(x += rhs, y += rhs); }

	Vector2 operator -= (float rhs) { return Vector2(x -= rhs, y -= rhs); }

	Vector2  operator/ (const Vector2 & rhs) const;

	Vector2 operator *(const Vector2 &rhs) const;
	
	Vector2 operator *=(const Vector2 &rhs);

	Vector2 operator +=(const Vector2 &rhs);

	Vector2 operator -=(const Vector2 &rhs);

	Vector2 operator * (float rhs) const{return Vector2(x * rhs, y * rhs);}

	float Length() const;

	float LengthSquared() const;
	
	float Dot(const Vector2 &other) const;

	float Cross(const Vector2 &other) const;

	float Distance(const Vector2 &rhs) const;

	float DistanceSquared(const Vector2 &rhs) const;

	void Set(float SetX, float SetY);

	Vector2 &Normal();

	Vector2 &Normalise();

};

