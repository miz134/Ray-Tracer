bool debug;

#include "Vector.h"
#include "AggregatePrimitive.h"
extern AggregatePrimitive aggregatePrimitive;


#include "Variables.h"
#include "Scene.h"
#include "readfile.h"
#include "Matrix.h"


int main(int argc, char* argv[])
{
	debug = true;
	Scene scene;
	readfile :: readFile(argv[1]);
	scene.render();
	aggregatePrimitive.deletePrimitives();
	/*
	Matrix m = Matrix(4.0f, 2.0f, 1.0f, 2.0f,
					2.0f, 3.0f, 4.0f, 1.0f,
					2.0f, 2.0f, 1.0f, 3.0f,
					1.0f, 2.0f, 3.0f, 1.0f);
					
	Matrix matrix = Matrix :: inverse(m);
	cout << Matrix :: determinant(m, 4) << endl;
	
	
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			cout << " r: " << r << " c: " << c << " | " << matrix.mat[r][c];
		}
		cout << endl;
	}
	*/
	vector<Light*>::iterator it;
	for (it = lights.begin(); it != lights.end(); it++)
	{
		delete *it;
	}
	//delete file;

}