#include "Color.h"

extern float shininess;

Color :: Color ()
{
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
}

Color :: Color (float r, float g, float b)
{
	red = r;
	green = g;
	blue = b;
}

Color Color :: add (Color& c1, Color& c2)
{
	float r = c1.red + c2.red;
	float g = c1.green + c2.green;
	float b = c1.blue + c2.blue;
	return Color(fminf(r, 1.0f), fminf(g, 1.0f), fminf(b, 1.0f));
}

Color Color :: subtract (Color& c1, Color& c2)
{
	float r = c1.red - c2.red;
	float g = c1.green - c2.green;
	float b = c1.blue - c2.blue;
	return Color(fminf(r, 1.0f), fminf(g, 1.0f), fminf(b, 1.0f));
}

Color Color :: multiply (float mul, Color& c)
{
	float r = mul * c.red;
	float g = mul * c.green;
	float b = mul * c.blue;
	return Color(fminf(r, 1.0f), fminf(g, 1.0f), fminf(b, 1.0f));
}

Color Color :: divide (float div, Color& c)
{
	float r = c.red / div;
	float g = c.green / div;
	float b = c.blue / div;
	return Color(fminf(r, 1.0f), fminf(g, 1.0f), fminf(b, 1.0f));
}

Color Color :: multiplyColor (Color& c1, Color& c2)
{
	float r = c1.red * c2.red;
	float g = c1.green * c2.green;
	float b = c1.blue * c2.blue;
	return Color(fminf(r, 1.0f), fminf(g, 1.0f), fminf(b, 1.0f));
}

#include <iostream>
using namespace std;
Color Color :: ComputeLight (Vector& direction, Color& lightcolor, Vector& normal, Vector& halfvec, Color& mydiffuse, Color& myspecular, float myshininess)
{
        float nDotL = Vector :: dot(normal, direction);
        Color tempLambert = Color :: multiplyColor(mydiffuse, lightcolor);
        Color lambert = Color :: multiply(fmaxf(nDotL, 0.0f), tempLambert);

        float nDotH = Vector :: dot(normal, halfvec); 
        Color tempPhong = Color :: multiplyColor(myspecular, lightcolor);
        float tempPow = pow(fmaxf(nDotH, 0.0f), myshininess);
        Color phong = Color :: multiply(tempPow, tempPhong);

        return Color :: add(lambert, phong);   
}    

Color Color :: shading (LocalGeo& local, BRDF& brdf, Ray& ray, Ray& lray, Color& color)
{
	Vector direction = lray.dir;
	Vector normal = local.normal;
	Vector halfvec = Vector :: subtract(lray.dir, ray.dir);
	halfvec = Vector :: normalize(halfvec);
	
	return ComputeLight(direction, color, normal, halfvec, *(brdf.kd), *(brdf.ks), shininess);
}

Color :: ~Color ()
{
	
}
