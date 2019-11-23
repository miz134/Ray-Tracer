#include "Intersection.h"

Intersection :: Intersection ()
{
}

Intersection :: Intersection (LocalGeo & local, GeometricPrimitive* prim)
{
	localGeo = local;
	primitive = prim;
}
