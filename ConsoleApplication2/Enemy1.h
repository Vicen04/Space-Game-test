#pragma once
#include "EnemyBase.h"
class Enemy1 :	public EnemyBase
{
public:
	Enemy1(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~Enemy1();
	void Update(float time);
	void Move();
};

