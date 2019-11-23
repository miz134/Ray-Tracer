#include "Light.h"

Light :: Light ()
{
}

Light :: Light(Vector& v, Color& c, bool point)
{
	vector = v;
	color = c;
	isPoint = point;
}
#include <iostream>

void Light :: generateLightRay(LocalGeo& local, Ray* lray, Color * lcolor)
{
	float min = 0.01f;
	float max = 10000.0f;
	Vector direction = vector;
	if (isPoint)
	{
		direction = Vector :: subtract(vector, local.pos);
		max = sqrt((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z)); 
		direction = Vector :: normalize(direction);
	}
	Vector epsilonShift = Vector :: multiply(0.001, direction);
	Vector epsilonPos = Vector :: add(local.pos, epsilonShift);
	*lray = Ray(epsilonPos, direction, min, max);
	*lcolor = color;
}
