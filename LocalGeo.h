#ifndef LOCALGEO_H
#define LOCALGEO_H

#include "Vector.h"

class LocalGeo
{
	public: 
		Vector pos;
		Vector normal;
		
		LocalGeo ();
		LocalGeo (Vector& p, Vector& n);
};

#endif