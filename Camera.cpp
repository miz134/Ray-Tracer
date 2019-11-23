#include "Camera.h"
#include "Variables.h"
#include "Vector.h"
#include <math.h>


Camera :: Camera ()
{
}

void Camera :: generateRay (Sampler& sample, Ray * ray)
{
	Vector a = Vector::subtract(eyeinit, center);
	Vector b = upinit;
	Vector w = Vector::normalize(a);
	Vector bCrossW = Vector::cross(b, w);
	Vector u = Vector::normalize(bCrossW);
	Vector v = Vector::cross(w, u);
	
	float halfWidth = globalWidth/2.0f;
	float halfHeight = globalHeight/2.0f;
	
	float fovyRadians = fovy * pi / 180.0f;
	
	float fovx = 2.0f * atan(tan(fovyRadians / 2.0f) * (((float) globalWidth)/((float) globalHeight)));
	
	float alpha = tan(fovx/2.0f) * ((sample.x + 0.5f - halfWidth)/halfWidth);
	float beta = tan(fovyRadians/2.0f) * ((halfHeight - 0.5f - sample.y)/halfHeight);
	
	Vector au = Vector::multiply(alpha, u);
	Vector bv = Vector::multiply(beta, v);
	Vector temp = Vector::add(au, bv);
	temp = Vector::subtract(temp, w);
	Vector dir = Vector::normalize(temp);
	
	float min = 0.0f;
	float max = 10000.0f;
	*ray = Ray(eyeinit, dir, min, max);
}
