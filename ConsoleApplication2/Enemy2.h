#pragma once
#include "EnemyBase.h"

class Player;

class Enemy2: public EnemyBase
{
public:
	Enemy2(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera);
	~Enemy2();
	void Update(float time);
	void Move();

private:
	bool _up;

};

