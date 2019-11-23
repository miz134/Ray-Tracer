#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>

#include "Matrix.h"

using namespace std;

class readfile
{
	public:
		static bool readvals(stringstream &s, const int numvals, float* values);
		static void rightmultiply(Matrix & M, stack<Matrix> &transfstack); 

		static void readFile(const char* filename); 
};

#endif