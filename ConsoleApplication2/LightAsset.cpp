#include "LightAsset.h"

LightAsset::LightAsset()
{
	_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	_diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	_specular = glm::vec3(0.4f, 0.4f, 0.4f);
	_position = glm::vec3(0.0f, 0.0f, 10.0f);
}

LightAsset::~LightAsset()
{

}