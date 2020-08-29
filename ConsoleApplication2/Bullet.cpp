#include "Bullet.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"

Bullet::Bullet(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Texture2D> texture, string type) : GameObject(_mesh, _transform, _rigidBody, _camera)
{
	SetType("bullet");
	SetTexture(texture);

	_type = type;

	if (_type == "player")
	{
		GetRigidBody()->SetVelocityFactor(250.0f);
		
	}
	else 
		GetRigidBody()->SetVelocityFactor(-250.0f);

	GetTransform()->SetScale(glm::vec3(16.0f, 16.0f, 1.0f));
	GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));

	if (_type == "boss")
		GetTransform()->SetScale(glm::vec3(24.0f, 24.0f, 1.0f));

	SetUpdate(true);
}

Bullet::~Bullet()
{

}

void Bullet::Move()
{
	GetRigidBody()->SetVelocity(glm::vec2(GetRigidBody()->GetVelocityFactor(), 0.0f));
}

void Bullet::Update(float time)
{

	Move();
	GetRigidBody()->Update(time);
	glm::vec2 velocity = GetRigidBody()->GetVelocity();
	glm::vec3 camera = GetCamera()->GetCameraSpeed();
	glm::vec3 position = GetTransform()->GetPosition();
	GetTransform()->SetPosition(glm::vec3(velocity.x + camera.x + position.x, velocity.y + camera.y + position.y, position.z));
	
	CheckIsOnScreen(GetTransform()->GetPosition(), GetCamera()->GetCameraPosition());
	GetTransform()->Update();

}

void Bullet::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
{
	glm::vec3 added = GetTransform()->GetScale();
	if (position.x + (added.x / 2.0f) < camera.x || position.x - (added.x / 2.0f) > camera.x + 1024.0f)
	{
		SetDestroy(true);
	}

}