#ifndef VARIABLES_H
#define VARIABLES_H

#include "Vector.h"
#include "AggregatePrimitive.h"
#include "Light.h"
#include <iostream>
#include <vector>
using namespace std;

extern bool debug;

extern int globalWidth;
extern int globalHeight;

extern Vector eyeinit;
extern Vector center;
extern Vector upinit;

extern float fovy;


extern float ambient[4];
extern float diffuse[4];
extern float specular[4];
extern float emission[4];
extern float shininess;

extern float attenuation[4];

extern int maxDepth;
extern int numLights;

extern vector<Light*> lights;

extern AggregatePrimitive aggregatePrimitive;

extern char* file;

#endif