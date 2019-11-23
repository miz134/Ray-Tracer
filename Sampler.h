#ifndef SAMPLER_H
#define SAMPLER_H

class Sampler
{
	public:
		float x;
		float y;
		int width;
		int height;
		Sampler ();
		Sampler (int w, int h);
		bool getSample (Sampler* sample);
};

#endif