#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Texture2D> texture, string type);
	~Bullet();
	void Move();
	void Update(float time);
	string GetBulletType() { return _type; }
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);

private:
	string _type;
};

