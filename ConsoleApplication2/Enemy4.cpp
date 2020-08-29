#include "Enemy4.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"
#include "Player.h"

Enemy4::Enemy4(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera, shared_ptr<Player> player) : EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(50);
	SetHealth(8);
	SetEnemyType("Enemy4");

	GetTransform()->SetScale(glm::vec3(90.0f, 90.0f, 1.0f));
	_player = player;
	GetRigidBody()->SetVelocityFactor(60.0f);
}
Enemy4::~Enemy4()
{

}

void Enemy4::Update(float time)
{
	if (GetTexture() == nullptr)
	{
		SetTexture(make_shared<Texture2D>());
		GetTexture()->Load("Textures/enemy4.png");
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

void Enemy4::Move()
{
	glm::vec3 player = _player->GetTransform()->GetPosition();
	glm::vec3 position = GetTransform()->GetPosition();
	if (player.y > position.y + 0.3f)
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x / 8.0f, GetRigidBody()->GetVelocityFactor()));
	else if (player.y < position.y - 0.3f)
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x / 8.0f, -GetRigidBody()->GetVelocityFactor()));
	else
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x / 8.0f, 0.0f));
}