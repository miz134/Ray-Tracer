#ifndef MATERIAL_H
#define MATERIAL_H

#include "LocalGeo.h"
#include "BRDF.h"

class Material
{
	public:
		BRDF *constantBRDF;
		Material ();
		Material (BRDF* brdf);
		void getBRDF (LocalGeo& local, BRDF* brdf);
		
		~Material ();
};

#endif