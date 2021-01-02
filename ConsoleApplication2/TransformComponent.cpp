#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include <glm/ext/matrix_transform.hpp>

TransformComponent::TransformComponent()
{
	_scale = glm::vec3(1.0f, 1.0f, 0.0f);
	_position = glm::vec3(1.0f, 1.0f, 0.0f);
	_rotation = 0;
}

TransformComponent::TransformComponent(glm::vec2 position, glm::vec2 scale, float rotation, bool scene)
{
	_scale = glm::vec3(scale, 1.0f);
	if (scene)
	    _position = glm::vec3(position, -1.0f);
	else
		_position = glm::vec3(position, 0.0f);
	_rotation = rotation;
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::Update()
{
	SetWorldMatrix();
}


void TransformComponent::SetWorldMatrix()
{
	_world = glm::mat4(1.0f);
	_world = glm::translate(_world, _position);
	_world = glm::rotate(_world, _rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	_world = glm::scale(_world, _scale);
}