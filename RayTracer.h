#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Color.h"
#include "Intersection.h"
#include "BRDF.h"
#include "math.h"

class RayTracer
{
	public: 
		void trace (Ray& ray, int depth, Color * color);
};

#endif