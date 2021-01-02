#pragma once
#include "EnemyBase.h"

//This is the first boss

class Boss1: public EnemyBase
{
public:
	Boss1(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~Boss1();
	void Update(float time);
	void Move();
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);
	void ResetShootTime() { SetShootTime(1.0f); }

private:
	bool _move = false, _up = false;
};

