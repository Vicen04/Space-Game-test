#include "EnemyBase.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "MaterialAsset.h"

EnemyBase::EnemyBase(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera) : GameObject(_mesh, _transform, _rigidBody, _camera)
{
	SetType("enemy");
	GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::CheckIsOnScreen(glm::vec3 position, glm::vec3 camera)
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
