#include "Boss2.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"

Boss2::Boss2(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera) : EnemyBase(mesh, transform, rigidBody, camera)
{
	SetScore(2000);
	SetHealth(50);
	SetEnemyType("boss");
	SetTexture(make_shared<Texture2D>());
	GetTexture()->Load("Textures/boss2.png");
	GetTransform()->SetScale(glm::vec3(156.0f, 177.0f, 1.0f));
	GetRigidBody()->SetVelocityFactor(75.0f);
}

Boss2::~Boss2()
{

}

void Boss2::Update(float time)
{
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

void Boss2::Move()
{
	glm::vec3 added = GetTransform()->GetScale();
	glm::vec3 position = GetTransform()->GetPosition();

	if (_up)
	{
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x, GetRigidBody()->GetVelocityFactor()));
		if (720.0f < position.y + added.y)
			_up = false;
	}
	else
	{
		GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x, -GetRigidBody()->GetVelocityFactor()));
		if (0.0f > position.y - added.y)
			_up = true;
	}

}

void Boss2::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
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