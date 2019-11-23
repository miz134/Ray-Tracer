#include "Transformation.h"

// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include <math.h>

Transformation :: Transformation ()
{
	m = Matrix();
}

Transformation :: ~Transformation ()
{

}

Transformation :: Transformation (Matrix matrix)
{
	m = matrix;
	minvt = Matrix :: inverse(matrix);
	minvt = Matrix :: transpose(minvt);
}

Transformation :: Transformation (Matrix matrix, Matrix matrixNormal)
{
	m = matrix;
	minvt = matrixNormal;
}

// Helper rotation function.  Please implement this.  
Matrix Transformation::rotate(const float degrees, const Vector& axis) 
{
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.  

	Vector axis1 = Vector :: normalize(axis);

	float radians = 	degrees * pi / 180.0f;
				  
	Matrix aat = Matrix(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z, 0.0f,
					axis.x * axis.y, axis.y * axis.y, axis.y * axis.z, 0.0f,
					axis.x * axis.z, axis.y * axis.z, axis.z * axis.z, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f);

	Matrix a = Matrix(0.0f, -axis.z, axis.y, 0.0f, 
					axis.z, 0.0f, -axis.x, 0.0f, 
					-axis.y, axis.x, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 0.0f);
					
	Matrix rotated = Matrix :: add(Matrix :: add(Matrix :: multiply(cos(radians), Matrix(1.0f)),
					Matrix :: multiply((1.0f - cos(radians)), aat)), 
					Matrix :: multiply(sin(radians), a));
	
	rotated.mat[3][3] = 1.0f;				
	return rotated;
}

void Transformation::left(float degrees, Vector& eye, Vector& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  Matrix rotated = Transformation :: rotate(-degrees, up);
  eye = Matrix :: multiplyVector(eye, rotated);
  up = Matrix :: multiplyVector(up, rotated);
}

void Transformation::up(float degrees, Vector& eye, Vector& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.  
  Matrix rotated = Transformation :: rotate(-degrees, Vector :: cross(eye, up));
  eye = Matrix :: multiplyVector(eye, rotated);
  up = Matrix :: multiplyVector(up, rotated);	
}
/*
Matrix Transformation::lookAt(const Vector &eye, const Vector &center, const Vector &up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  
  Vector w = normalize(eye);
  Vector u = Vector :: normalize(Vector :: cross(up, eye));
  Vector v = Vector :: normalize(Vector :: cross(w, u));
  Vector e = eye;

  Matrix la = Matrix(u.x, u.y, u.z, -(u.x * e.x) - (u.y * e.y) - (u.z * e.z),
				 v.x, v.y, v.z, -(v.x * e.x) - (v.y * e.y) - (v.z * e.z),
				 w.x, w.y, w.z, -(w.x * e.x) - (w.y * e.y) - (w.z * e.z),
				 0.0f, 0.0f, 0.0f, 1.0f);
  return la;
}
*/

/*
Matrix Transformation::perspective(float fovy, float aspect, float zNear, float zFar)
{
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  float radians = fov/2.0f * pi/180.f;
  float d = 1.0f/tan(radians);
  Matrix persp = Matrix(d/aspect, 0.0f, 0.0f, 0.0f, 
					0.0f, d, 0.0f, 0.0f, 
					0.0f, 0.0f, -(zFar + zNear)/(zFar - zNear), (-2 *
					zFar * zNear)/(zFar - zNear), 
					0.0f, 0.0f, -1.0f, 0.0f);
  return persp;
}
*/

Matrix Transformation::scale(const float &sx, const float &sy, const float &sz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  Matrix scale = Matrix(sx, 0.0f, 0.0f, 0.0f,
					0.0f, sy, 0.0f, 0.0f,
					0.0f, 0.0f, sz, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
  return scale;
}

Matrix Transformation::translate(const float &tx, const float &ty, const float &tz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
  Matrix translate = Matrix(1.0f, 0.0f, 0.0f, tx, 
						0.0f, 1.0f, 0.0f, ty, 
						0.0f, 0.0f, 1.0f, tz, 
						0.0f, 0.0f, 0.0f, 1.0f);
  return translate;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

Vector Transformation::upvector(const Vector &up, const Vector & zvec) 
{
  Vector x = Vector :: cross(up,zvec); 
  Vector y = Vector :: cross(zvec,x); 
  Vector ret = Vector :: normalize(y); 
  return ret; 
}


Vector Transformation :: multiply (Matrix& matrix, Vector& vector)
{
	float newX = matrix.mat[0][0] * vector.x + matrix.mat[0][1] * vector.y + matrix.mat[0][2] * vector.z;
	float newY = matrix.mat[1][0] * vector.x + matrix.mat[1][1] * vector.y + matrix.mat[1][2] * vector.z;
	float newZ = matrix.mat[2][0] * vector.x + matrix.mat[2][1] * vector.y + matrix.mat[2][2] * vector.z;
	return Vector(newX, newY, newZ);

}

Ray Transformation :: multiply (Transformation& trans, Ray& ray)
{
	Vector newPos = multiply(trans.m, ray.pos);

	newPos.x += trans.m.mat[0][3];
	newPos.y += trans.m.mat[1][3];
	newPos.z += trans.m.mat[2][3];

	Vector newDir = multiply(trans.m, ray.dir);
	return Ray(newPos, newDir, ray.t_min, ray.t_max);
}

#include <iostream>
using namespace std;

LocalGeo Transformation :: multiply (Transformation& trans, LocalGeo * local)
{
	Vector newPos = multiply(trans.m, local -> pos);

	newPos.x += trans.m.mat[0][3];
	newPos.y += trans.m.mat[1][3];
	newPos.z += trans.m.mat[2][3];
	

	Vector newNormal = multiply(trans.minvt, local -> normal);
	newNormal = Vector :: normalize (newNormal);

	return LocalGeo (newPos, newNormal);
}



