CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
CFLAGS = -O3 -funroll-loops -g -DGL_GLEXT_PROTOTYPES -DGL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED -DOSX -Wno-deprecated-register -Wno-deprecated-declarations -Wno-shift-op-parentheses
INCFLAGS = -I./glm-0.9.7.1 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./lib/mac/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
else
CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./glm-0.9.7.1 -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L./lib/nix/ \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lGLEW -lglut -lGLU -lGL -lX11 -lfreeimage
endif

RM = /bin/rm -f 
#all: transforms
#transforms: main.o shaders.o Transform.o readfile.o display.o variables.h readfile.h shaders.h Transform.h grader.o UCSD/grader.h \
#	   Geometry.o
#	$(CC) $(CFLAGS) -o transforms shaders.o main.o Transform.o Geometry.o readfile.o display.o grader.o $(INCFLAGS) $(LDFLAGS) 
#main.o: main.cpp shaders.h Transform.h variables.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
#shaders.o: shaders.cpp shaders.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c shaders.cpp
#readfile.o: readfile.cpp readfile.h variables.h 
#	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
#display.o: display.cpp variables.h Geometry.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c display.cpp
#Transform.o: Transform.cpp Transform.h 
#	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp  
#grader.o: UCSD/grader.cpp UCSD/grader.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c UCSD/grader.cpp
#Geometry.o: Geometry.cpp Geometry.h Transform.h variables.h
#	$(CC) $(CFLAGS) $(INCFLAGS) -c Geometry.cpp
all: mains
mains: main.o AggregatePrimitive.o BRDF.o Camera.o Color.o Film.o GeometricPrimitive.o Intersection.o Light.o LocalGeo.o Material.o Matrix.o Ray.o RayTracer.o readfile.o Sampler.o Scene.o Shape.o Transformation.o Vector.o
	$(CC) $(CFLAGS) -o raytracer main.o AggregatePrimitive.o BRDF.o Camera.o Color.o Film.o GeometricPrimitive.o Intersection.o Light.o LocalGeo.o Material.o Matrix.o Ray.o RayTracer.o readfile.o Sampler.o Scene.o Shape.o Transformation.o Vector.o $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
AggregatePrimitive.o: AggregatePrimitive.cpp AggregatePrimitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c AggregatePrimitive.cpp
BRDF.o: BRDF.cpp BRDF.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c BRDF.cpp
Camera.o: Camera.cpp Camera.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Camera.cpp
Color.o: Color.cpp Color.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Color.cpp
Film.o: Film.cpp Film.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Film.cpp
GeometricPrimitive.o: GeometricPrimitive.cpp GeometricPrimitive.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c GeometricPrimitive.cpp
Intersection.o: Intersection.cpp Intersection.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Intersection.cpp
LocalGeo.o: LocalGeo.cpp LocalGeo.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c LocalGeo.cpp
Light.o: Light.cpp Light.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Light.cpp
Material.o: Material.cpp Material.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Material.cpp
Matrix.o: Matrix.cpp Matrix.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Matrix.cpp
Ray.o: Ray.cpp Ray.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Ray.cpp
RayTracer.o: RayTracer.cpp RayTracer.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c RayTracer.cpp
readfile.o: readfile.cpp readfile.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
Sampler.o: Sampler.cpp Sampler.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Sampler.cpp
Scene.o: Scene.cpp Scene.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Scene.cpp
Shape.o: Shape.cpp Shape.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Shape.cpp
Transformation.o: Transformation.cpp Transformation.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transformation.cpp
Vector.o: Vector.cpp Vector.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c Vector.cpp
clean: 
	$(RM) *.o transforms *.png


 
