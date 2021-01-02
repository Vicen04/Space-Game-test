#pragma once
#include <glm/vec2.hpp> 

class GameObject;

class RigidbodyComponent
{
public:
	RigidbodyComponent();
	~RigidbodyComponent();
	void PhysicsResponse(GameObject* object);
	glm::vec2 GetVelocity() { return _velocity; }
	void SetVelocity(glm::vec2 velo) { _velocity = velo; }
	void SetFrictionFactor(float frictionFactor) { _frictionFactor = frictionFactor; }
	void SetVelocityFactor(float velo) { _velocityFactor = velo; }
	float GetVelocityFactor() {return _velocityFactor; }
	void SetBounciness(float bounciness) { _bounciness = bounciness; }
	void SetMass(float mass) { _mass = mass; }
	void Update(float time);


private:
	void UpdateGravity(float time);
	void UpdateVelocity(float time);
	void UpdateFriction();

	glm::vec2 _velocity, _gravity, _friction, _force, _external;
	float _frictionFactor, _mass, _bounciness = 0.0f, _velocityFactor = 10.0f;


};

