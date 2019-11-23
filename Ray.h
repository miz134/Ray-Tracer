#ifndef RAY_H
#define RAY_H

#include "Vector.h"
#include "LocalGeo.h"

class Ray
{
	public: 
		Vector pos;
		Vector dir;
		float t_min;
		float t_max;
		
		Ray ();
		Ray (Vector& p, Vector& v, float min, float max);
		static Ray createReflectRay(LocalGeo& local, Ray& ray);

};

#endif
