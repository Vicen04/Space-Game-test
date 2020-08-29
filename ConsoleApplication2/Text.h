#pragma once
#include "structures.h"
#include <map>

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Text
{
public:
	Text();
	Text(const char* filename);
	~Text();

	void RenderText(GLuint shader, std::string text, float x, float y, float scale, glm::vec3 color);

private:
	std::map<GLchar, Character> Characters;
	unsigned int _vertexArrayBuffer, _vertexBuffer;
	glm::mat4 projection = glm::ortho(0.0f, 1024.0f, 0.0f, 720.0f);
};

