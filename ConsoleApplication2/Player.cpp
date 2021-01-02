#include "Player.h"
#include "CollisionDetection.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Texture2D.h"
#include "CameraComponent.h"
#include <glm/trigonometric.hpp>  
#include <iostream>

Player::Player()
{
	SetTexture(make_shared<Texture2D>());
	GetTexture()->Load("Textures/spaceship_small_blue.png");
	GetTransform()->SetPosition(glm::vec3(100.0f, 360.0f, 0.0f));
	GetTransform()->SetRotation(glm::radians(-90.0f));
	GetTransform()->SetScale(glm::vec3(90.0f, 84.0f, 0.0f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	GetMesh()->SetColor(originalColor, true);
	GetRigidBody()->SetVelocityFactor(75.0f);
	_left = _right = _up = _down = false;
	SetType("player");
	SetUpdate(true);
}

Player::Player(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera): GameObject(mesh, transform, rigidBody, camera)
{
	SetTexture(make_shared<Texture2D>());
	GetTexture()->Load("Textures/spaceship_small_blue.png");
	GetTransform()->SetPosition(glm::vec3(100.0f, 360.0f, 0.0f));
	GetTransform()->SetRotation(glm::radians(-90.0f));
	GetTransform()->SetScale(glm::vec3(90.0f, 84.0f, 0.0f));
	
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	originalColor.push_back(glm::vec3(1.0f, 0.65f, 0.65f));
	GetMesh()->SetColor(originalColor, true);
	GetRigidBody()->SetVelocityFactor(75.0f);
	_left = _right = _up = _down = false;
	SetType("player");
	SetUpdate(true);
}

Player::~Player()
{
	cout << "Player destroyed" << endl;
}

void Player::Reset()
{
	GetTransform()->SetPosition(glm::vec3(100.0f, 360.0f, 0.0f));
	_left = _right = _up = _down = _shoot = false;
	_shield = _bomb = _score = 0;
	_bullets = 1;
	_lives = 3;
	_timeToShoot = _invincibility = 0.0f;
	_speed = _shootSpeed = 1.0f;
}

void Player::Move()
{
	glm::vec2 velocity = GetRigidBody()->GetVelocity();
	float velocityFactor = GetRigidBody()->GetVelocityFactor();

	if (_left || _right || _up || _down)
	{
		if (_left)
			GetRigidBody()->SetVelocity(glm::vec2(-velocityFactor * _speed, velocity.y));
		else if (_right)
			GetRigidBody()->SetVelocity(glm::vec2(velocityFactor * _speed, velocity.y));

		velocity = GetRigidBody()->GetVelocity();
		if (_up)
			GetRigidBody()->SetVelocity(glm::vec2(velocity.x, velocityFactor * _speed));
		else if (_down)
			GetRigidBody()->SetVelocity(glm::vec2(velocity.x, -velocityFactor * _speed));
	}
	else
		GetRigidBody()->SetVelocity(glm::vec2(0.0f, 0.0f));
}

void Player::Update(float time)
{
	if (_timeToShoot > 0.0f)
		_timeToShoot = _timeToShoot - time * _shootSpeed;

	if (_timeToBomb > 0.0f)
		_timeToBomb = _timeToBomb - time;

	if (_invincibility > 0.0f)
	{
		_invincibility = _invincibility - time;
		if (_invincibility < 0.3f)
			GetMesh()->SetColor(originalColor, true);
	}

	Move();
	GetRigidBody()->Update(time);
	glm::vec2 velocity = GetRigidBody()->GetVelocity();
	glm::vec3 camera = GetCamera()->GetCameraSpeed();
	glm::vec3 position = GetTransform()->GetPosition();
	GetTransform()->SetPosition(glm::vec3(velocity.x + camera.x + position.x, velocity.y + camera.y + position.y, position.z));
	CheckIsOnScreen(GetTransform()->GetPosition(), GetCamera()->GetCameraPosition());
	GetTransform()->Update();

}

void Player::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
{
	glm::vec3 added = GetTransform()->GetScale();
	if (position.x - (added.x / 2.0f) < camera.x)
	{
		GetTransform()->SetPosition(glm::vec3(camera.x + 0.1f + (added.x/2.0f), position.y, position.z));
	}
	else if (position.x + (added.x / 2.0f) > camera.x + 1024.0f)
	{
		GetTransform()->SetPosition(glm::vec3(camera.x + 1023.9f - (added.x / 2.0f), position.y, position.z));
	}
	position = GetTransform()->GetPosition();
	if (position.y - (added.y / 2.0f) < camera.y)
	{
		GetTransform()->SetPosition(glm::vec3(position.x, camera.y + 0.1f + (added.y / 2.0f), position.z));
	}
	else if (position.y + (added.y / 2.0f) > camera.y + 720.0f)
	{
		GetTransform()->SetPosition(glm::vec3(position.x , camera.y + 719.9f - (added.y / 2.0f), position.z));
	}
}

void Player::TakeDamage()
{
	if (_shield > 0)
	{
		_shield--;
	}
	else
		_lives--;

	_invincibility = 3.0f;

	vector<glm::vec3> color;
	color.push_back(glm::vec3(1.0f, 0.35f, 0.35f));
	color.push_back(glm::vec3(1.0f, 0.35f, 0.35f));
	color.push_back(glm::vec3(1.0f, 0.35f, 0.35f));
	color.push_back(glm::vec3(1.0f, 0.35f, 0.35f));
	GetMesh()->SetColor(color, true);
}