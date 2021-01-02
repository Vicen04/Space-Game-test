#pragma once
#include <glm/mat4x4.hpp> 
#include <glm/vec3.hpp> 
#include <glm/vec2.hpp>  

class TransformComponent
{
public:

	TransformComponent(glm::vec2 position, glm::vec2 scale, float rotation, bool scene);
	TransformComponent();
	~TransformComponent();

	void Update();

	void SetWorldMatrix();
	glm::mat4 GetWorldMatrix() { return _world; }

	void SetPosition(glm::vec3 position) { _position = position; }
	void SetScale(glm::vec3 scale) { _scale = scale; }
	void SetRotation(float rotation) { _rotation = rotation; }

	glm::vec3 GetPosition() { return _position; }
	glm::vec3 GetScale() { return _scale; }
	float GetRotation() { return _rotation; }

private:

	glm::vec3 _position;
	glm::vec3 _scale;
	float _rotation;

	glm::mat4 _world;

};