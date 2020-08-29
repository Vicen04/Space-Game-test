#include "Bounciness.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"

Bounciness::Bounciness()
{
	_bounciness = 0.0f;
}

void Bounciness::SetBounciness(GameObject* gameobject)
{
	gameobject->GetRigidBody()->SetBounciness(_bounciness);
}
