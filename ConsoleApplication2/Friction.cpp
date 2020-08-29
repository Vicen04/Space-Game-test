#include "Friction.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"

Friction::Friction()
{
	_frictionFactor = 0.3f;
}

void Friction::SetFriction(GameObject* gameobject)
{
	gameobject->GetRigidBody()->SetFrictionFactor(_frictionFactor);
}