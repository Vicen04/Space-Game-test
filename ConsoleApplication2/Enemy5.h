#pragma once
#include "EnemyBase.h"

class Player;
class Enemy5: public EnemyBase
{
public:
	Enemy5(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Player> player);
	~Enemy5();
	void Update(float time);
	void Move();
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);
	void ResetShootTime() { SetShootTime(1.5f); }

private:
	shared_ptr<Player> _player;
	bool _move = false;
};

