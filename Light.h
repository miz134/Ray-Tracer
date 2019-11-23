#ifndef LIGHT_H
#define LIGHT_H

#include "LocalGeo.h"
#include "Ray.h"
#include "Color.h"
#include <math.h>

class Light
{
	public: 
		Vector vector;
		Color color;
		bool isPoint;
		
		Light ();
		
		Light (Vector& v, Color& c, bool point);
		void generateLightRay (LocalGeo& local, Ray* lray, Color * lcolor);
};

#endif