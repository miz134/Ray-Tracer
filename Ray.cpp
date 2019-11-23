#include "Ray.h"

Ray :: Ray ()
{
	t_min = 0.01f;
	t_max = 10000.0f;
}

Ray :: Ray (Vector& p, Vector& v, float min, float max)
{
	pos = p;
	dir = v;
	t_min = min;
	t_max = max;
}

Ray Ray :: createReflectRay(LocalGeo& local, Ray& ray)
{
	float normalDotP1Times2 = 2.0f * Vector :: dot(local.normal, ray.dir);
	//Vector normalDotP1Times2MulP1 = Vector :: multiply(normalDotP1Times2, ray.dir);

	Vector normalDotP1Times2MulNormal = Vector :: multiply(normalDotP1Times2, local.normal);
	Vector newDir = Vector :: subtract(ray.dir, normalDotP1Times2MulNormal);
	newDir = Vector :: normalize(newDir);
	return Ray(local.pos, newDir, 0.01f, 10000.0f);

}
