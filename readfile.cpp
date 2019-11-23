int globalWidth;
int globalHeight;
#include "Vector.h"	
#include "AggregatePrimitive.h"
#include "Material.h"
#include "BRDF.h"
#include "Light.h"
#include <vector>

Vector eyeinit;
Vector center;
Vector upinit;
float fovy;
float ambient[4];
float diffuse[4];
float specular[4];
float emission[4];
float shininess;

float attenuation[4];
int maxDepth;
int numLights;
char* file;


vector<Light*> lights;


AggregatePrimitive aggregatePrimitive;

#include "Variables.h"
#include "readfile.h"
#include <string>





// Function to read the input data values
// Use is optional, but should be very helpful in parsing.  
bool readfile :: readvals(stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

void readfile :: rightmultiply(Matrix & M, stack<Matrix> &transfstack) 
{
  Matrix &T = transfstack.top(); 
  T = Matrix :: multiplyMatrix(T, M); 
}

void readfile :: readFile(const char* filename) 
{
	vector<GeometricPrimitive* > list;
	int maxVertices = 8;
	int currentVertices = 0;
	Vector *vertices = new Vector[maxVertices];
	if (debug)
	{
		cerr << "Reading file" << endl;
	}
  	string str, cmd; 
  	ifstream in;
  	in.open(filename);
  	maxDepth = 5;
  	//file = new char[12];
  	file = (char *) "myScene.png";

  	stack <Matrix> transfstack; 
    transfstack.push(Matrix(1.0f));  
    attenuation[0] = 1;
    attenuation[1] = 0;
    attenuation[2] = 0;
    ambient[0] = 0.2;
    ambient[1] = 0.2;
    ambient[2] = 0.2;	
  	if (in.is_open()) {

    getline (in, str); 
    while (in) {
      	if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str);
        s >> cmd; 
        int i; 
        float values[10]; // Position and color for light, colors for others
        // Up to 10 params for cameras.  
        bool validinput; // Validity of input 
        
        

        if (cmd == "size") {
          validinput = readvals(s,2,values); 
          if (validinput) { 
            globalWidth = (int) values[0];
            globalHeight = (int) values[1]; 
          } 
        } else if (cmd == "camera") {
          validinput = readvals(s,10,values); // 10 values eye cen up fov
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE
            // Use all of values[0...9]
            // You may need to use the upvector fn in Transform.cpp
            // to set up correctly. 
            // Set eyeinit upinit center fovy in variables.h 
			
			eyeinit = Vector(values[0], values[1], values[2]);
			center = Vector(values[3], values[4], values[5]);
			upinit = Vector(values[6], values[7], values[8]);
			//upinit = Transformation::upvector(upinit, Vertex::subtract(center, eyeinit));
			//upinit = Transform::upvector(upinit, center - eyeinit);

			fovy = values[9];
          }
        }
        else if (cmd == "maxverts")
        {
        	validinput = readvals(s, 1, values);
        	if (validinput)
        	{
        		maxVertices = values[0];
        		delete[] vertices;
        		vertices = new Vector[maxVertices];
        		//
        	}
        }
        else if (cmd == "vertex")
        {
        	validinput = readvals(s, 3, values);
        	if (validinput)
        	{
        		if (currentVertices < maxVertices)
        		{
        			vertices[currentVertices] = Vector(values[0], values[1], values[2]);
        			currentVertices++;
        		}
        	}
        }
        else if (cmd == "tri")
        {
        	validinput = readvals(s, 3, values);
        	if (validinput)
        	{
        		Shape* shape = new Shape(vertices[(int) values[0]], vertices[(int) values[1]], vertices[(int) values[2]]);
        		Matrix transf = transfstack.top();
        		Matrix invTransf = Matrix :: inverse(transf);
        		Matrix normalTransf = Matrix :: transpose(invTransf);
        		Transformation objToWorld = Transformation(transf, normalTransf);
        		Transformation worldToObj = Transformation(invTransf);
        		Color* dif = new Color(diffuse[0], diffuse[1], diffuse[2]);
        		Color* spe = new Color(specular[0], specular[1], specular[2]);
        		Color* amb = new Color(ambient[0], ambient[1], ambient[2]);
        		Color* emi = new Color(emission[0], emission[1], emission[2]);
        		BRDF* brdf = new BRDF(dif, spe, amb, emi);
        		Material* material = new Material(brdf);
        		GeometricPrimitive* geoPrim = new GeometricPrimitive(objToWorld, worldToObj, shape, material);
        		list.push_back(geoPrim);
        	}
        }
        else if (cmd == "sphere")
        {
        	validinput = readvals(s, 4, values);
        	if (validinput)
        	{
        		Vector vector = Vector(values[0], values[1], values[2]);
        		Shape* shape = new Shape(vector, values[3]);
        		Matrix transf = transfstack.top();
        		Matrix invTransf = Matrix :: inverse(transf);
        		Matrix normalTransf = Matrix :: transpose(invTransf);
        		Transformation objToWorld = Transformation(transf, normalTransf);
        		Transformation worldToObj = Transformation(invTransf);
        		Color* dif = new Color(diffuse[0], diffuse[1], diffuse[2]);
        		Color* spe = new Color(specular[0], specular[1], specular[2]);
        		Color* amb = new Color(ambient[0], ambient[1], ambient[2]);
        		Color* emi = new Color(emission[0], emission[1], emission[2]);
        		BRDF* brdf = new BRDF(dif, spe, amb, emi);
        		Material* material = new Material(brdf);
        		GeometricPrimitive* geoPrim = new GeometricPrimitive(objToWorld, worldToObj, shape, material);
        		list.push_back(geoPrim);
        	}
        }
        else if (cmd == "ambient") {
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              ambient[i] = values[i]; 
            }
          }
        } else if (cmd == "diffuse") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              emission[i] = values[i]; 
            }
          }
        }
        else if (cmd == "attenuation")
        {
        	validinput = readvals(s, 3, values);
        	if (validinput)
        	{
        		for (i = 0; i < 3; i++)
        		{
        			attenuation[i] = values[i];
        		}
        	}
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values); 
          if (validinput) {
            shininess = values[0]; 
          }
        }
        else if (cmd == "translate") {
          validinput = readvals(s,3,values); 
          if (validinput) {
          	Matrix tempMatrix = Transformation :: translate(values[0], values[1], values[2]);
			rightmultiply(tempMatrix, transfstack);
          }
        }
        else if (cmd == "scale") {
          validinput = readvals(s,3,values); 
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE.  
            // Think about how the transformation stack is affected
            // You might want to use helper functions on top of file.  
            // Also keep in mind what order your matrix is!
            Matrix tempMatrix = Transformation :: scale(values[0], values[1], values[2]);
			rightmultiply(tempMatrix, transfstack);
          }
        }
        else if (cmd == "rotate") {
          validinput = readvals(s,4,values); 
          if (validinput) {

            // YOUR CODE FOR HW 2 HERE. 
            // values[0..2] are the axis, values[3] is the angle.  
            // You may want to normalize the axis (or in Transform::rotate)
            // See how the stack is affected, as above.  
            // Note that rotate returns a mat3. 
            // Also keep in mind what order your matrix is!
            Vector tempVector = Vector(values[0], values[1], values[2]);
            Matrix tempMatrix = Transformation :: rotate(values[3], tempVector);
			rightmultiply(tempMatrix, transfstack);			
		  }
        }

        // I include the basic push/pop code for matrix stacks
        else if (cmd == "point")
        {
        	validinput = readvals(s, 6, values);
        	if (validinput)
        	{
        		Vector vector = Vector(values[0], values[1], values[2]);
        		Color color = Color(values[3], values[4], values[5]);
        		Light * light = new Light(vector, color, true);
        		lights.push_back(light);
        		numLights++;
        	}
        }
        else if (cmd == "directional")
        {
        	validinput = readvals(s, 6, values);
        	if (validinput)
        	{
        	    Vector vector = Vector(values[0], values[1], values[2]);
				Color color = Color(values[3], values[4], values[5]);
        		lights.push_back(new Light(vector, color, false));
        		numLights++;
        	}
        }

        else if (cmd == "maxdepth")
        {
        	validinput = readvals(s, 1, values);
        	if (validinput)
        	{
        		maxDepth = (int) values[0];
        	}
        }

        
        else if (cmd == "output")
        {
        	string name;
        	s >> name;
        	//delete file;
        	cout << name << endl;
        	file = new char[name.size() + 1];
			strcpy(file, name.c_str());

        	cout << "Outputting to file: " << file << endl;
        }
        

        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        }
        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n"; 
        }
      }
      getline (in, str); 
    }

    // Set up initial position for eye, up and amount
    // As well as booleans 
/*
    eye = eyeinit; 
    up = upinit; 
    amount = amountinit;
    sx = sy = 1.0;  // keyboard controlled scales in x and y 
    tx = ty = 0.0;  // keyboard controllled translation in x and y  
*/	cout << "Finished reading" << endl;
	aggregatePrimitive = AggregatePrimitive (list);
  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n"; 
    throw 2; 
  }
  delete[] vertices;
}
