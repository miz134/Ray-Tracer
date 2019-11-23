#ifndef BRDF_H
#define BRDF_H

class Color;

class BRDF
{
	public:
		Color* kd;
		Color* ks;
		Color* ka;
		Color* kr;
		
		BRDF ();
		BRDF (Color* d, Color* s, Color* a, Color* r);
		
		~BRDF ();
};

#endif