#include "Enemy1.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"

Enemy1::Enemy1(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera) : EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(10);
	SetHealth(2);
	SetEnemyType("enemy1");
	GetTransform()->SetScale(glm::vec3(58.0f, 60.0f, 1.0f));
}
Enemy1::~Enemy1()
{
	
}

void Enemy1::Update(float time)
{
	if (GetTexture() == nullptr)
	{
		SetTexture(make_shared<Texture2D>());
		GetTexture()->Load("Textures/enemy1.png");
	}
	if (GetUpdate())
	{
		Move();
		glm::vec2 velocity = GetRigidBody()->GetVelocity();
		glm::vec3 position = GetTransform()->GetPosition();
		GetTransform()->SetPosition(glm::vec3(velocity.x + position.x, position.y, position.z));
	}
	CheckIsOnScreen(GetTransform()->GetPosition(), GetCamera()->GetCameraPosition());
	GetTransform()->Update();
}

void Enemy1::Move()
{
	GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x / 2.0f, 0.0f));
}
