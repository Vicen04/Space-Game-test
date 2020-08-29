#include "Enemy2.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"
#include "Player.h"

Enemy2::Enemy2(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera) : EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(20);
	SetHealth(4);
	SetEnemyType("enemy2");
	GetTransform()->SetScale(glm::vec3(64.0f, 64.0f, 1.0f));
	GetRigidBody()->SetVelocityFactor(35.0f);
}
Enemy2::~Enemy2()
{

}

void Enemy2::Update(float time)
{

	if (GetTexture() == nullptr)
	{
		SetTexture(make_shared<Texture2D>());
		GetTexture()->Load("Textures/enemy2.png");
	}

	if (GetUpdate())
	{
		Move();
		glm::vec2 velocity = GetRigidBody()->GetVelocity();
		glm::vec3 position = GetTransform()->GetPosition();
		GetTransform()->SetPosition(glm::vec3(velocity.x + position.x, position.y + velocity.y * time, position.z));
	}
	CheckIsOnScreen(GetTransform()->GetPosition(), GetCamera()->GetCameraPosition());
	GetTransform()->Update();
}

void Enemy2::Move()
{
	glm::vec3 added = GetTransform()->GetScale();
	glm::vec3 position = GetTransform()->GetPosition();

	if (_up)
	{
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x/ 4.0f, GetRigidBody()->GetVelocityFactor()));
		if (720.0f < position.y + added.y)
			_up = false;
	}
	else
	{
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x / 4.0f, -GetRigidBody()->GetVelocityFactor()));
		if (0.0f > position.y - added.y)
			_up = true;
	}
}
