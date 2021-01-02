#include "Texture2D.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


Texture2D::Texture2D()
{
}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}


bool Texture2D::LoadRAW(const char* path, int width, int height)
{
	ifstream inFile;
	_width = width; _height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); //Seek to end of file
	int fileSize = (int)inFile.tellg(); //Get current position in file - The End, this gives us total file size
	char* tempTextureData = new char[fileSize]; //Create an new aray to store data
	inFile.seekg(0, ios::beg); //Seek back to beginning of file
	inFile.read(tempTextureData, fileSize); //Read in all the data in one go
	inFile.close(); //Close the file

	cout << path << " loaded." << endl;

	glGenTextures(2, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	delete[] tempTextureData; //Clear up the data
	return true;
}

bool Texture2D::Load(const char* path)
{
	glGenTextures(2, &_ID); //Get next Texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID

	unsigned char* texture = stbi_load(path, &_width, &_height, &_colorChannels, 0);

	if (texture)
	{
		if (_colorChannels == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << path << " has been loaded" << std::endl;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(texture); //Clear up the data
	return true;
}

GLuint Texture2D::GetID() const
{
	return _ID;
}

int Texture2D::GetWidth() const
{
	return _width;
}

int Texture2D::GetHeight() const
{
	return _height;
}

int Texture2D::GetColorChannels() const
{
	return _colorChannels;
}

