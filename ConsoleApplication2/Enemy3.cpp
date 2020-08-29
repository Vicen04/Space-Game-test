#include "Enemy3.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"

Enemy3::Enemy3(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera) : EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(50);
	SetHealth(5);
	SetEnemyType("enemy3");

	GetTransform()->SetScale(glm::vec3(80.0f, 80.0f, 1.0f));
}
Enemy3::~Enemy3()
{

}

void Enemy3::Update(float time)
{
	if (GetTexture() == nullptr)
	{
		SetTexture(make_shared<Texture2D>());
		GetTexture()->Load("Textures/enemy3.png");
	}

	if (GetUpdate() && _move)
	{
		if (GetShootTime() > 0.0f)
		SetShootTime(GetShootTime() - time);
		Move();
		glm::vec2 velocity = GetRigidBody()->GetVelocity();
		glm::vec3 position = GetTransform()->GetPosition();
		GetTransform()->SetPosition(glm::vec3(velocity.x + position.x, velocity.y * time + position.y, position.z));
	}
	CheckIsOnScreen(GetTransform()->GetPosition(), GetCamera()->GetCameraPosition());
	GetTransform()->Update();
}

void Enemy3::Move()
{
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x, 0.0f));
}

void Enemy3::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
{
	glm::vec3 added = GetTransform()->GetScale();
	if (position.x + (added.x / 2.0f) < camera.x)
	{
		SetDestroy(true);
	}
	else if (position.x - (added.x / 2.0f) > camera.x + 1024.0f)
	{
		SetUpdate(false);
	}
	else
		SetUpdate(true);

	if (position.x + (added.x / 2.0f) < camera.x + 1000.0f)
		_move = true;
}