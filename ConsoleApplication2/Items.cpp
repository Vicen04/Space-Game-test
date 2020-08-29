#include "Items.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "MaterialAsset.h"

Items::Items(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera, shared_ptr<Texture2D> texture, string type) : GameObject(_mesh, _transform, _rigidBody, _camera)
{
	SetType("item");
	SetTexture(texture);
	_type = type;
	GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	GetTransform()->SetScale(glm::vec3(30.0f, 30.0f, 1.0f));
	SetUpdate(true);
}

Items::~Items()
{
	
}

void Items::Move()
{
	GetRigidBody()->SetVelocity(glm::vec2(GetCamera()->GetCameraSpeed().x/2.0f, 0.0f));
}

void Items::Update(float time)
{
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

void Items::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
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
}