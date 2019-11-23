#include "Shape.h"

Shape :: Shape (Vector& c, float r)
{
	isSphere = true;
	center = c;
	radius = r;
}

Shape :: Shape (Vector& x1, Vector& y1, Vector& z1)
{
	isSphere = false;
	x = x1;
	y = y1;
	z = z1;
}
		
bool Shape :: intersect (Ray& ray, float* thit, LocalGeo* local)
{
	if (isSphere)
	{
		return intersectCircle(ray, thit, local);
	}
	return intersectTriangle(ray, thit, local);
}

bool Shape :: intersectP (Ray& ray)
{
	float tempThit = 0.0f;
	LocalGeo tempLocal = LocalGeo();
	return intersect(ray, &tempThit, &tempLocal);
	
}
		
bool Shape :: intersectCircle (Ray& ray, float* thit, LocalGeo* local)
{
	//cout << "intersect?";
	float dirDotDir = Vector :: dot(ray.dir, ray.dir);
	Vector posSubCenter = Vector :: subtract(ray.pos, center);
	float rSquared = radius * radius;
	

	float a = dirDotDir;
	float b = 2 * Vector :: dot(ray.dir, posSubCenter);
	float c = Vector :: dot(posSubCenter, posSubCenter) - rSquared;
	
	float insideRoot = (b * b) - (4 * a * c);
	float root = 0;

	
	if (insideRoot < 0.0f)
	{

		//cout << "1" << insideRoot << endl;
		return false;
	}
	if (insideRoot > 0)
	{
		root = sqrt(insideRoot);
	}
	float root1 = (-b + root)/(2 * a);
	float root2 = (-b - root)/(2 * a);
	float closestRoot;
	float epsilon = 0.00001f;
	// tangent
	if (root1 >= root2 - epsilon && root1 <= root2 + epsilon)
	{
		closestRoot = root1;
	}
	// inside sphere
	else if (root1 > epsilon && root2 > epsilon)
	{
		if (root1 < root2)
		{
			closestRoot = root1;
		}
		else
		{
			closestRoot = root2;
		}
	}
	/*
	else if ((root1 < 0 || root2 < 0) && (root1 > 0 || root2 > 0))
	{
		if (root1 > 0)
		{
			closestRoot = root1;
		}
		else if (root2 > 0)
		{
			closestRoot = root2;
		}
	}
	*/
	else
	{
		return false;
	}
	if (closestRoot > ray.t_max)
	{
		return false;
	}

	Vector dirMulRoot = Vector :: multiply(closestRoot, ray.dir);
	Vector pos = Vector :: add(ray.pos, dirMulRoot);
	Vector norm = Vector :: subtract(pos, center);
	norm = Vector :: normalize(norm);
	LocalGeo l = LocalGeo(pos, norm);
	*thit = closestRoot;
	*local = l;
	//cerr << "Intersect" << endl;
	return true;
}
		
bool Shape :: intersectTriangle (Ray& ray, float* thit, LocalGeo* local)
{
	Vector a = x;
	Vector b = y;
	Vector c = z;
	Vector cSubA = Vector :: subtract(c, a);
	Vector bSubA = Vector :: subtract(b, a);
	//Vector cSubACrossBSubA = Vector :: cross(cSubA, bSubA);
	Vector cSubACrossBSubA = Vector :: cross(bSubA, cSubA);
	Vector n = Vector :: normalize(cSubACrossBSubA);
	float aDotN = Vector :: dot(a, n);
	float posDotN = Vector :: dot(ray.pos, n);
	float dirDotN = Vector :: dot(ray.dir, n);
	float t = (aDotN - posDotN)/dirDotN;
	float epsilon = 0.001f;
	
	if (t < epsilon)
	{
		return false;
	}
	
	if (t > ray.t_max - epsilon)
	{
		return false;
	}

	Vector dirMulT = Vector :: multiply(t, ray.dir);
	Vector p = Vector :: add(ray.pos, dirMulT);
	Vector norm = Vector :: normalize(cSubACrossBSubA);
	
	Vector h = Vector :: cross (ray.dir, bSubA);
	float aa = Vector :: dot (cSubA, h);
	if (aa == 0)
	{
		return false;
	}
	float f = 1.0f/aa;
	Vector s = Vector :: subtract (ray.pos, a);
	float u = f * Vector :: dot(s, h);
	if (u < 0 || u > 1)
	{
		return false;
	}
	Vector q = Vector :: cross (s, cSubA);
	float v = f * Vector :: dot(ray.dir, q);
	if (v < 0 || u + v > 1)
	{
		return false;
	}
	LocalGeo l = LocalGeo(p, norm); 
	*thit = t;
	*local = l;
	return true;
		
	
	/*
	NOT WORKING?
	float areaOfTriangle = Vector :: dot(bSubA, cSubA)/2.0f;
	Vector pSubA = Vector :: subtract(p, a);
	Vector pSubB = Vector :: subtract(p, b);
	Vector pSubC = Vector :: subtract(p, c);
	float areaAPC = Vector :: dot(pSubA, pSubC)/2.0f;
	float areaAPB = Vector :: dot(pSubA, pSubB)/2.0f;
	float areaBPC = Vector :: dot(pSubB, pSubC)/2.0f;


	
	
	float alpha = areaAPC/areaOfTriangle;
	float beta = areaAPB/areaOfTriangle;
	float gamma = areaBPC/areaOfTriangle;
	
	if ((alpha + beta + gamma) >= 0 && (alpha + beta + gamma) <= 1)
	{
		cout << "t: " << t << " alpha: " << alpha << " beta: " << beta << " gamma: " << gamma << endl;
		LocalGeo l = LocalGeo(p, norm); 
		thit = &t;
		local = &l;
		return true;
	}
	
	return false;
	*/
}



