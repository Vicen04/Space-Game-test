#include "MaterialAsset.h"
#include <GL/glew.h>

MaterialAsset::MaterialAsset(bool texture)
{
	if (!texture)
	{
		_ambient = glm::vec3(0.8f, 0.5f, 0.5f);
		_diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	}
	_specular = glm::vec3(0.0f, 0.0f, 1.0f);
	_shininess = 100.0f;
}

MaterialAsset::~MaterialAsset()
{

}