#ifndef CAMERA_H
#define CAMERA_H

#include "Sampler.h"
#include "Ray.h"

class Camera
{
	public:
		void generateRay (Sampler& sample, Ray * ray);
		Camera ();
		
};

#endif