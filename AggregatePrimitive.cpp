#include "AggregatePrimitive.h"


AggregatePrimitive :: AggregatePrimitive ()
{
}


AggregatePrimitive :: AggregatePrimitive (vector<GeometricPrimitive*> list)
{
	l = list;
}


bool AggregatePrimitive :: intersect (Ray& ray, float* thit, Intersection* in)
{
	vector<GeometricPrimitive*>::iterator it;
	float temp;
	Intersection tempIn;
	bool intersected = false;
	for (it = l.begin(); it != l.end(); it++)
	{
		if((*it) -> intersect (ray, &temp, &tempIn))
		{			
			if (temp < *thit)
			{
				*thit = temp;
				*in = tempIn;
			}
			intersected = true;
		}
	}
	return intersected;
}

bool AggregatePrimitive :: intersectP (Ray& ray)
{
	vector<GeometricPrimitive*>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		if ((*it) -> intersectP (ray))
		{
			return true;
		}
	}
	return false;
}

void AggregatePrimitive :: deletePrimitives ()
{
	vector<GeometricPrimitive*>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		delete *it;
	}
}