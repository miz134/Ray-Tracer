#include "GeometricPrimitive.h"


GeometricPrimitive :: GeometricPrimitive (Transformation otw, Transformation wto, Shape* s, Material * mat)
{
	objToWorld = otw;
	worldToObj = wto;
	shape = s;
	material = mat;
}

bool GeometricPrimitive :: intersect (Ray& ray, float *thit, Intersection * in)
{

	Ray oray = Transformation :: multiply (worldToObj, ray);
	LocalGeo olocal;
	if (!shape -> intersect(oray, thit, &olocal))
	{
		return false;
	}
	in -> primitive = this;
	in -> localGeo = Transformation :: multiply (objToWorld, &olocal);
	return true;
}

bool GeometricPrimitive :: intersectP (Ray& ray)
{

	Ray oray = Transformation :: multiply (worldToObj, ray);
	ray.dir = Vector :: normalize(ray.dir);
	return shape -> intersectP(oray);
}

void GeometricPrimitive :: getBRDF (LocalGeo& local, BRDF* brdf)
{
	material -> getBRDF(local, brdf);
}

GeometricPrimitive :: ~GeometricPrimitive ()
{
	delete shape;
	delete material;
}