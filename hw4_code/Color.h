#ifndef COLOR_H
#define COLOR_H

#include "LocalGeo.h"

#include "Ray.h"
#include "Vector.h"
#include <algorithm>
#include "math.h"
#include "BRDF.h"

class BRDF;

class Color
{
	public: 
		float red;
		float green;
		float blue;
		Color ();
		Color (float r, float g, float b);
		
		static Color add (Color& c1, Color& c2);
		static Color subtract (Color& c1, Color& c2);
		static Color multiply (float mul, Color& c2);
		static Color divide (float div, Color& c2);
		static Color multiplyColor (Color& c1, Color& c2);
		
		static Color ComputeLight (Vector& direction, Color& lightcolor, Vector& normal, Vector& halfvec, Color& mydiffuse, Color& myspecular, float myshininess);

		static Color shading (LocalGeo& local, BRDF& brdf, Ray& ray, Ray& lray, Color& color);

		
		~Color();
};

#endif
