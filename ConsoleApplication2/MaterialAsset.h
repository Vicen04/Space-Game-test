#pragma once
#include <glm/vec3.hpp> 

typedef float GLfloat;

class MaterialAsset
{
public:
	MaterialAsset(bool HasTexture);
	MaterialAsset(char* path, bool HasTexture);
	~MaterialAsset();

	glm::vec3 GetAmbient() { return _ambient; }
	glm::vec3 GetDiffuse() { return _diffuse; }
	glm::vec3 GetSpecular() { return _specular; }
	GLfloat GetShininess() { return _shininess; }

	void SetAmbient(glm::vec3 ambient) { _ambient = ambient; }
	void SetDiffuse(glm::vec3 diffuse) { _diffuse = diffuse; }
	void SetSpecular(glm::vec3 specular) { _specular = specular; }
	void SetShininess(GLfloat shininess) { _shininess = shininess; }

private:
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	GLfloat _shininess;
};

