#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H

#include "Shape.h"
#include "Ray.h"
#include "Transformation.h"
#include "Intersection.h"
#include "Material.h"
#include "BRDF.h"

class GeometricPrimitive
{
	public:
		Transformation objToWorld;
		Transformation worldToObj;
		Shape* shape;
		Material* material;

		GeometricPrimitive (Transformation otw, Transformation wto, Shape* s, Material* mat);
		bool intersect (Ray& ray, float *thit, Intersection * in);
		bool intersectP (Ray& ray);
		void getBRDF (LocalGeo& local, BRDF* brdf);
		
		~GeometricPrimitive();
};

#endif