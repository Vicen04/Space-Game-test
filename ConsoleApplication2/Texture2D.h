#pragma once
#include "structures.h"

class Texture2D
{
public:
	Texture2D();
	~Texture2D();

	// used to load .RAW files
	bool LoadRAW(const char* path, int width, int height);
	//for JPG, PNG, BMP
	bool Load(const char* path);

	GLuint GetID() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetColorChannels() const;

private:
	GLuint _ID;
	int _width, _height, _colorChannels;
};

