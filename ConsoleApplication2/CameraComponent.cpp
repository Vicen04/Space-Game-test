#include "CameraComponent.h"

CameraComponent::CameraComponent(float screenWidth, float screenHeight)
{
	_position.x = 0.0f;
	_position.y = 0.0f;
	_position.z = 3.0f;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

CameraComponent::CameraComponent(glm::vec2 position, float screenWidth, float screenHeight)
{
	_position.x = position.x;
	_position.y = position.y;
	_position.z = 3.0f;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::UpdateMatrices()
{
	_view = glm::lookAt(_position,  _position + _cameraTarget, _cameraUp);
	_projection = glm::ortho(0.0f, _screenWidth , 0.0f, _screenHeight , 0.1f, 100.0f);
}

void  CameraComponent::UpdatePosition(float time) 
{
	_cameraSpeed.x = 50.0f * time;
	_cameraSpeed.y = 0.0f;
	_cameraSpeed.z = 0.0f;

	_position = _position + _cameraSpeed;

}