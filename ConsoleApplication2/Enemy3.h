#pragma once
#include "EnemyBase.h"

class Player;

class Enemy3: public EnemyBase
{
public:
	Enemy3(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~Enemy3();
	void Update(float time);
	void Move();
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);

private:
	bool _move = false;
};

