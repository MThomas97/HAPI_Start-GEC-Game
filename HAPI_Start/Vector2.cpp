#include "Vector2.h"


Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	return Vector2(x+rhs.x, y+rhs.y);
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}



Vector2 Vector2::operator/(const Vector2 &rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

Vector2 Vector2::operator*(const Vector2 &rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator*=(const Vector2 &rhs) 
{
	 return Vector2(x *= rhs.x, y *= rhs.y);
}

Vector2 Vector2::operator+=(const Vector2 &rhs)
{
	return Vector2(x += rhs.x, y += rhs.y);
}

Vector2 Vector2::operator-=(const Vector2 &rhs)
{
	return Vector2(x -= rhs.x, y -= rhs.y);
}

float Vector2::Length() const
{
	return sqrt(x*x + y*y);
}

float Vector2::LengthSquared() const
{
	return x*x + y*y;
}

//void Vector2::NormaliseInPlace()
//{
//	float len = Length();
//
//	if (len == 0)
//		return;
//	
//	x /= len;
//	y /= len;
//}

float Vector2::Dot(const Vector2 &other) const
{
	return x * other.x + y * other.y;
}

float Vector2::Cross(const Vector2 &other) const
{
	return x * other.y - y * other.x;
}

float Vector2::Distance(const Vector2 &rhs) const
{
	return sqrt(((x - rhs.x) * (x - rhs.x)) + ((y - rhs.y) * (y - rhs.y)));
}

float Vector2::DistanceSquared(const Vector2 &rhs) const
{
	return ((x - rhs.x) * (x - rhs.x)) + ((y - rhs.y) * (y - rhs.y));
}

void Vector2::Set(float SetX, float SetY)
{
	x = SetX;
	y = SetY;
}

Vector2 & Vector2::Normal()
{
	Set(-y, x);
	return *this;
}

Vector2 & Vector2::Normalise()
{
	if (Length() != 0)
	{
		float len = Length();
		x /= len;
		y /= len;
		return *this;
	}
	
	x = y = 0;
	return *this;
}


