#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H

#include <vector>
#include "GeometricPrimitive.h"
#include <iostream>
using namespace std;

class AggregatePrimitive 
{
	public:
		vector<GeometricPrimitive*> l;
		AggregatePrimitive ();
		AggregatePrimitive (vector<GeometricPrimitive*> list);
		bool intersect (Ray& ray, float* thit, Intersection* in);
		bool intersectP (Ray& ray);
		
		void deletePrimitives();
		
};

#endif