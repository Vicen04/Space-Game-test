#pragma once
#include "GameObject.h"
class Player;

class Ally : public GameObject
{
public:
	Ally(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Player> player, shared_ptr<Texture2D> texture);
	~Ally();
	void Move();
	void Update(float time);
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);

private:
	shared_ptr<Player> _player;

};

