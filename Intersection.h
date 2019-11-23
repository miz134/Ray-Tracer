#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "LocalGeo.h"



class GeometricPrimitive;

class Intersection
{
	public: 
		LocalGeo localGeo;
		GeometricPrimitive* primitive;
		Intersection ();
		Intersection (LocalGeo & local, GeometricPrimitive* prim);
};

#endif