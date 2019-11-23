#ifndef SHAPE_H
#define SHAPE_H

#include "Vector.h"
#include "Ray.h"
#include "LocalGeo.h"
#include <math.h>
//debugging
#include <iostream>
using namespace std;


class Shape
{
	public:
		bool isSphere;
		float radius;
		Vector center;
		Vector x;
		Vector y;
		Vector z;
		
		Shape (Vector& c, float r);
		Shape (Vector& x1, Vector& y1, Vector& z1);
		
		bool intersect (Ray& ray, float* thit, LocalGeo* local);
		bool intersectP (Ray& ray);
		
		bool intersectCircle (Ray& ray, float* thit, LocalGeo* local);
		bool intersectTriangle (Ray& ray, float* thit, LocalGeo* local);
};

#endif

