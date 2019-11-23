#include "Sampler.h"

#include "Variables.h"


Sampler :: Sampler()
{
	x = 0.0f;
	y = 0.0f;
}

Sampler :: Sampler(int w, int h)
{
	x = 0.0f;
	y = 0.0f;
	width = w;
	height = h;
}

bool Sampler :: getSample(Sampler * sample)
{
	float currX = sample -> x;
	float currY = sample -> y;
	if (sample -> x >= width)
	{
		currX = 0;
		currY++;
	}
	else
	{
		currX++;
	}
	sample -> x = currX;
	sample -> y = currY;
	if (debug)
	{
		int PixelsPerTwenty = height/20;
		if (currX == 0 && (int) currY % PixelsPerTwenty == 0)
		{
			float progress =  ((float) (currY * (float) width + currX))/((float) (width * height)) * 100.0f;
			cout << "Scene Progress: " << progress << "%" << endl;
		}
	}
	if (currY > height)
	{
		return false;
	}
	return true;
	
}
