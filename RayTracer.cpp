#include "RayTracer.h"

#include "Variables.h"

/*
// USE ONLY TO TEST RANDOM COLORS
#include <stdlib.h>
#include <time.h>
using namespace std;
*/



void RayTracer :: trace (Ray & ray, int depth, Color * color)
{
	float thit = 10000.0f;
	Intersection in;
	BRDF brdf;
	if (depth > maxDepth)
	{
		*color = Color (0.0f, 0.0f, 0.0f);
		return;
	}
	if (!aggregatePrimitive.intersect(ray, &thit, &in))
	{
		*color = Color (0.0f, 0.0f, 0.0f);
		return;
	}
	LocalGeo local = LocalGeo();
	in.primitive -> getBRDF(local, &brdf);
	*color = Color :: add(*(brdf.ka), *(brdf.kr));

	for (int i = 0; i < numLights; i++)
	{
		Ray lray;
		Color lcolor;
		lights[i] -> generateLightRay(in.localGeo, &lray, &lcolor);
		if (!aggregatePrimitive.intersectP(lray))
		{
			Color shaded = Color :: shading(in.localGeo, brdf, ray, lray, lcolor);
			if (lights[i] -> isPoint)
			{
				//Vector dist = Vector :: subtract(in.localGeo.pos, lray.pos);
				Vector dist = Vector :: subtract(in.localGeo.pos, lights[i] -> vector);
				float d = sqrt((dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z));
				//cout << "d: " << d << endl;
				//cout << attenuation[0] << " " << attenuation[1] << " " << attenuation[2] << endl;
				float attenuationValue = 1.0f/(attenuation[0] + (attenuation[1]*d) + (attenuation[2]* d * d));
				//cout << attenuationValue << endl;
				shaded = Color :: multiply(attenuationValue, shaded);
				// SCENE 6 NORMAL TRIANGLES ARE PROBABLY WRONG?
			}
			*color = Color :: add(*color, shaded);
		}
	}

	if (brdf.ks -> red > 0 || brdf.ks -> green > 0 || brdf.ks -> blue > 0)
	{
		Color tempColor;
		Ray reflectRay = Ray :: createReflectRay(in.localGeo, ray);
		
		trace(reflectRay, depth + 1, &tempColor);
		Color newColor = Color :: multiplyColor(*(brdf.ks), tempColor);
		*color = Color :: add(*color, newColor);
	}


	//delete in;
}