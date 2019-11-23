#include "Film.h"
extern char* file;
#include <iostream>

Film :: Film (int w, int h)
{
	width = w;
	height = h;
	pixels = new unsigned char[width * height * 3];
}

void Film :: commit (Sampler& sample, Color& color)
{
	int index = 3 * width * sample.y + 3 * sample.x;
	pixels[index] = (char) (color.blue * 255.0f);
	pixels[index + 1] = (char) (color.green * 255.0f);
	pixels[index + 2] = (char) (color.red * 255.0f);
	
}

void Film :: writeImage ()
{
	FreeImage_Initialise();
	
	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, true);

	FreeImage_Save(FIF_PNG, img, file, 0);

	FreeImage_DeInitialise();
}

Film :: ~Film()
{
	//delete[] pixels;
}	

