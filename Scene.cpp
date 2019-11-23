#include "Scene.h"
#include "Variables.h"


void Scene :: render ()
{
	Sampler sample = Sampler(globalWidth, globalHeight);
	RayTracer raytracer;
	Ray ray;
	Color color;
	Camera camera;
	Film film = Film(globalWidth, globalHeight);
	if (debug)
	{
		cerr << "Rendering " << endl;
	}
	bool gotSample = true;
	while (gotSample)
	{
		int depth = 0;
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, depth, &color);
		film.commit(sample, color);
		gotSample = sample.getSample(&sample);
		depth++;
	}
	if (debug)
	{
		cerr << "writeImage" << endl;
	}
	film.writeImage();
}