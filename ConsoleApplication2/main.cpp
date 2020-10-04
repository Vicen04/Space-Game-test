
#include "EngineManager.h"
#include <Windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) 
{
	srand(time(NULL));
	EngineManager* engine = new EngineManager(argc, argv);
	
	engine->Start();

	glutMainLoop();

	delete engine;

	return 0; 
}
