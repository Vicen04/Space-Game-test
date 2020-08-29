#pragma once

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
