#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
	public:
		float x;
		float y;
		float z;
		Vector ();
		Vector (float newX, float newY, float newZ);
		
		
		static Vector add (const Vector& v1, const Vector& v2);
		static Vector subtract (const Vector& v1, const Vector& v2);
		static Vector multiply (float mul, const Vector& v);
		static Vector divide (float div, const Vector& v);
		
		static float magnitude (const Vector& v);
		static Vector normalize (const Vector& v);
		static Vector cross (const Vector& v1, const Vector& v2);
		static float dot (const Vector& v1, const Vector& v2);
		
		
};

#endif