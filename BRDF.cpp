#include "BRDF.h"

BRDF :: BRDF ()
{
/*
	kd = new Color();
	ks = new Color();
	ka = new Color();
	kr = new Color();
	*/
}

BRDF :: BRDF (Color* d, Color* s, Color* a, Color* r)
{
	kd = d;
	ks = s;
	ka = a;
	kr = r;
}

BRDF :: ~BRDF ()
{
	//delete kd;
	//delete ks;
	//delete ka;
	//delete kr;
}
