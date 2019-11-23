#ifndef FILM_H
#define FILM_H

#include "Sampler.h"
#include "Color.h"
#include "FreeImage.h"

class Film
{
	public: 
		int width;
		int height;
		unsigned char* pixels;
		Film (int width, int height);
		
		void commit (Sampler& sample, Color& color);
		void writeImage();
		~Film();
};

#endif