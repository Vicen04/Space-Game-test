#pragma once
#define GLEW_STATIC 1
#define FREEGLUT_LIB_PRAGMAS 0

#define REFRESHRATE 16

class EngineManager;

namespace GLUTCallbacks
{
	void Init(EngineManager* gl);
	void Display();
	void Timer(int preferredRefresh);
	void KeyboardKeyPressed(unsigned char key, int x, int y);
	void KeyboardKeyUp(unsigned char key, int x, int y);
	void MouseHandler(int button, int state, int x, int y);
}
