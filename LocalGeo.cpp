#include "LocalGeo.h"

LocalGeo :: LocalGeo ()
{
}

LocalGeo :: LocalGeo (Vector& p, Vector& n)
{
	pos = p;
	normal = n;
}