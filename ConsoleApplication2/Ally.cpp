#include "Ally.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"
#include "Player.h"

Ally::Ally(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Player> player, shared_ptr<Texture2D> texture) : GameObject(_mesh, _transform, _rigidBody, _camera)
{
	SetType("ally");
	SetTexture(texture);
	GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	GetTransform()->SetScale(glm::vec3(24.0f, 24.0f, 1.0f));
	SetUpdate(true);
	_player = player;
}

Ally::~Ally()
{

}

void Ally::Move()
{

}

void Ally::Update(float time)
{
	glm::vec2 velocity = _player->GetRigidBody()->GetVelocity();
	glm::vec3 camera = GetCamera()->GetCameraSpeed();
	glm::vec3 position = GetTransform()->GetPosition();
	GetTransform()->SetPosition(glm::vec3(velocity.x + camera.x + position.x, velocity.y + camera.y + position.y, position.z));
	GetTransform()->Update();

}

void Ally::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
{

}