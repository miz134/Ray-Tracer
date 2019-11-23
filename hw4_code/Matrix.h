#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include "Vector.h"

class Matrix
{
	public:
		float mat[4][4];
		Matrix ();
		Matrix (float x);
		Matrix (float x, float y, float z, float w);
		Matrix (float x0, float x1, float x2, float x3, 
				float y0, float y1, float y2, float y3,
				float z0, float z1, float z2, float z3,
				float w0, float w1, float w2, float w3);
		Matrix (float m[4][4]);
		
		static Matrix add (const Matrix& m1, const Matrix& m2);
		static Matrix subtract (const Matrix& m1, const Matrix& m2);
		static Matrix multiply (float mul, const Matrix& m);
		static Matrix divide (float div, const Matrix& m);
		static Matrix transpose (const Matrix& m);

		static Matrix multiplyMatrix (const Matrix& m1, const Matrix& m2);
		
		static Vector multiplyVector (const Matrix& m, const Vector& v);

		static Vector multiplyVector (const Vector& v, const Matrix& m);
		
		static Matrix cofactor (const Matrix& m, int row, int col, int size);
		static float determinant (const Matrix& m, int size);
		
		static Matrix inverse (const Matrix& m);

	
};

#endif