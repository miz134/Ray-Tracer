#ifndef SCENE_H
#define SCENE_H

#include "Sampler.h"
#include "RayTracer.h"
#include "Color.h"
#include "Film.h"
#include "Camera.h"



class Scene {
	public:
		void render();
};

#endif