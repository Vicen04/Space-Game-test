#pragma once
#include <glm/vec2.hpp>              
#include <glm/vec3.hpp>                            
#include <glm/mat4x4.hpp>            

class CameraComponent 
{
public:
	CameraComponent(float screenWidth, float screenHeight);
	CameraComponent(glm::vec2 position, float screenWidth, float screenHeight);
	~CameraComponent();
	void MoveLeft(float value) { _position.x = _position.x - value; }
	void MoveRight(float value) { _position.x = _position.x + value; }
	void MoveUp(float value) { _position.y = _position.y + value; }
	void MoveDown(float value) { _position.y = _position.y - value; }
	void UpdateMatrices();
	void UpdatePosition(float time);
	glm::vec3 GetCameraPosition() { return _position; }
	void ResetCameraPosition() {_position = glm::vec3(0.0f, 0.0f, 3.0f); }
	glm::vec3 GetCameraSpeed() { return _cameraSpeed; }


	glm::mat4 GetViewMatrix() { return _view; }
	glm::mat4 GetProjectionMatrix() { return _projection; }

private:
	glm::vec3 _position, _cameraSpeed;
	float _screenWidth, _screenHeight;
	glm::vec3 _cameraTarget = glm::vec3(0.0f, 0.0f, -10.0f);
	glm::vec3 _cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 _view;
	glm::mat4 _projection;
};

