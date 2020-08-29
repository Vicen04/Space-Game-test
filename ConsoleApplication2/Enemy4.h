#pragma once
#include "EnemyBase.h"

class Player;

class Enemy4: public EnemyBase
{
public:
	Enemy4(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Player> player);
	~Enemy4();
	void Update(float time);
	void Move();

private:
	shared_ptr<Player> _player;

};

