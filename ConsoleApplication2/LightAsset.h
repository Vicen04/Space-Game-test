#pragma once
#include "structures.h"

class LightAsset
{
public:
	LightAsset();
	LightAsset(char* path);
	~LightAsset();

	glm::vec3 GetAmbient() { return _ambient; }
	glm::vec3 GetDiffuse() { return _diffuse; }
	glm::vec3 GetSpecular() { return _specular; }
	glm::vec3 GetPosition() { return _position; }

	void SetAmbient(glm::vec3 ambient) { _ambient = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { _diffuse = diffuse; }
	void SetSpecular(glm::vec3 specular) { _specular = specular; }
	void SetPosition(glm::vec3 position) { _position = position; }


private:
	glm::vec3 _ambient, _diffuse, _specular, _position;
};

