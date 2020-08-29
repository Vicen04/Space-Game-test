
#include "EngineManager.h"
#include <Windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <time.h>



bool editor = true;

int main(int argc, char* argv[]) 
{
	srand(time(NULL));
	auto* engine = new EngineManager(argc, argv);
	
	engine->Start();

	glutMainLoop();

	return 0; 
}
