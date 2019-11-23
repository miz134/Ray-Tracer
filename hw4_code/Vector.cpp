#include "Vector.h"
#include "math.h"


Vector :: Vector ()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector :: Vector (float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}


Vector Vector :: add (const Vector& v1, const Vector& v2)
{
	float newX = v1.x + v2.x;
	float newY = v1.y + v2.y;
	float newZ = v1.z + v2.z;
	return Vector(newX, newY, newZ);
}

Vector Vector :: subtract (const Vector& v1, const Vector& v2)
{
	float newX = v1.x - v2.x;
	float newY = v1.y - v2.y;
	float newZ = v1.z - v2.z;
	return Vector(newX, newY, newZ);
}

Vector Vector :: multiply (float mul, const Vector& v)
{
	float newX = mul * v.x;
	float newY = mul * v.y;
	float newZ = mul * v.z;
	return Vector(newX, newY, newZ);
}

Vector Vector :: divide (float div, const Vector& v)
{
	float newX = v.x / div;
	float newY = v.y / div;
	float newZ = v.z / div;
	return Vector(newX, newY, newZ);
}

float Vector :: magnitude (const Vector& v)
{
	return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

Vector Vector :: normalize (const Vector& v)
{
	float mag = magnitude(v);
	return Vector :: divide (mag, v);
}

Vector Vector :: cross (const Vector& v1, const Vector& v2)
{
	float newX = v1.y * v2.z - v1.z * v2.y;
	float newY = v1.z * v2.x - v1.x * v2.z;
	float newZ = v1.x * v2.y - v1.y * v2.x;
	return Vector(newX, newY, newZ);
}

float Vector :: dot (const Vector& v1, const Vector& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}