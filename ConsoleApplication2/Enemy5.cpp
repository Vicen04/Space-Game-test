#include "Enemy5.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"
#include "Player.h"

Enemy5::Enemy5(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera, shared_ptr<Player> player): EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(100);
	SetHealth(10);
	SetEnemyType("enemy5");

	GetTransform()->SetScale(glm::vec3(120.0f, 120.0f, 1.0f));
	GetRigidBody()->SetVelocityFactor(75.0f);
	_player = player;
}
Enemy5::~Enemy5()
{

}

void Enemy5::Update(float time)
{
	if (GetTexture() == nullptr)
	{
		SetTexture(make_shared<Texture2D>());
		GetTexture()->Load("Textures/enemy5.png");
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

void Enemy5::Move()
{
	glm::vec3 player = _player->GetTransform()->GetPosition();
	glm::vec3 position = GetTransform()->GetPosition();
	if (player.y > position.y + 0.5f)
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x, GetRigidBody()->GetVelocityFactor()));
	else if (player.y < position.y -0.5f)
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x , -GetRigidBody()->GetVelocityFactor()));
	else 
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x, 0.0f));
}

void Enemy5::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
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