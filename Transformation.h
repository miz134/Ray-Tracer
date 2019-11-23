#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

const float pi = 3.14159265 ; // For portability across platforms

#include "Matrix.h"
#include "Vector.h"
#include "LocalGeo.h"
#include "Ray.h"

class Transformation 
{
	public:
		Transformation ();
		Transformation (Matrix matrix);
		Transformation (Matrix matrix, Matrix matrixNormal);
		virtual ~Transformation();
		
		Matrix m;
		Matrix minvt;

		static void left(float degrees, Vector& eye, Vector& up);
		static void up(float degrees, Vector& eye, Vector& up);
		//static Matrix lookAt(const Vector& eye, const Vector &center, const Vector& up);
		//static Matrix perspective(float fovy, float aspect, float zNear, float zFar);
        static Matrix rotate(const float degrees, const Vector& axis);
        static Matrix scale(const float &sx, const float &sy, const float &sz); 
        static Matrix translate(const float &tx, const float &ty, const float &tz);
        static Vector upvector(const Vector &up, const Vector &zvec); 

        static Vector multiply (Matrix& mat, Vector& vec);
        static Ray multiply (Transformation& trans, Ray& ray);
        static LocalGeo multiply (Transformation& trans, LocalGeo * local);

};

#endif