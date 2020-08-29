#include "RigidbodyComponent.h"
#include "GameObject.h"

RigidbodyComponent::RigidbodyComponent()
{
	_mass = 1.0f;
	_frictionFactor = 0.0f;
}

RigidbodyComponent::~RigidbodyComponent()
{

}

void RigidbodyComponent::Update(float physicsDeltaTime)
{
	//UpdateGravity(physicsDeltaTime);
	UpdateVelocity(physicsDeltaTime);
	if (_frictionFactor != 0.0f)
	UpdateFriction();
	//_external = glm::vec2(0.0f, 0.0f);
}



void RigidbodyComponent::UpdateGravity(float time)
{
	//multiplied by the framerate
	_gravity = glm::vec2(0.0f, -9.8f);
	_gravity = _gravity * time;
}

void RigidbodyComponent::UpdateVelocity(float time)
{
	//glm::vec2 acceleration = _force / _mass;
	_velocity = _velocity * time;
	//_velocity = _velocity + _external;
}

void RigidbodyComponent::UpdateFriction()
{
	float multiplier;
	if (_velocity.y < 0)
	    multiplier = -cos(atan2f(_velocity.x, _velocity.y));
	else
		multiplier = cos(atan2f(_velocity.x, _velocity.y));

	_friction = _gravity * -_mass;
	_friction = _friction + (_velocity * multiplier);
	_friction = _friction * _frictionFactor;
}

void RigidbodyComponent::PhysicsResponse(GameObject* object)
{
	glm::vec2 velocity2 =  object->GetRigidBody()->GetVelocity();

	if (_velocity.x > velocity2.x)
		_external.x += -_velocity.x + _bounciness * -_velocity.x;
	else
		_external.x += velocity2.x;

	if (_velocity.y > velocity2.y)
		_external.y += -_velocity.y + _bounciness * -_velocity.y;
	else
		_external.y += velocity2.y;
	       
}