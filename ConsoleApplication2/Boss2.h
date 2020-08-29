#pragma once
#include "EnemyBase.h"
class Boss2 :
	public EnemyBase
{
public:
	Boss2(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~Boss2();
	void Update(float time);
	void Move();
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);
	void ResetShootTime() { SetShootTime(1.0f); }

private:
	bool _move = false, _up = false;
};

