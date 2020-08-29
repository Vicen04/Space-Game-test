#include "Level1.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Items.h"
#include "MaterialAsset.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Enemy5.h"
#include "Enemy4.h"
#include "Enemy3.h"
#include "Bullet.h"
#include "Boss1.h"
#include "Texture2D.h"

Level1::Level1(shared_ptr<Text> text, shared_ptr<CameraComponent> camera, shared_ptr<Player> player): SceneBase(text, camera, player)
{
	SetBackground("Textures/space.png");
	AddObjects(player);

	shared_ptr<Texture2D> enemy1 = make_shared<Texture2D>();
	enemy1->Load("Textures/enemy1.png");

	shared_ptr<Texture2D> enemy2 = make_shared<Texture2D>();
	enemy2->Load("Textures/enemy2.png");

	shared_ptr<Texture2D> enemy3 = make_shared<Texture2D>();
	enemy3->Load("Textures/enemy3.png");

	shared_ptr<Texture2D> enemy4 = make_shared<Texture2D>();
	enemy4->Load("Textures/enemy4.png");

	shared_ptr<Texture2D> enemy5 = make_shared<Texture2D>();
	enemy5->Load("Textures/enemy5.png");


	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(1300.0f, 600.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(1100.0f, 400.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(1500.0f, 500.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);


	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(1700.0f, 100.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy2>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(2100.0f, 500.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy2);

	AddObjects(make_shared<Enemy3>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(2800.0f, 350.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy3);

	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(2500.0f, 650.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy4>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(3200.0f, 400.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera, player));
	GetLastGameObject()->SetTexture(enemy4);

	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(3500.0f, 250.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy2>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(3700.0f, 200.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy2);

	AddObjects(make_shared<Enemy1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(3000.0f, 570.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));
	GetLastGameObject()->SetTexture(enemy1);

	AddObjects(make_shared<Enemy5>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(3500.0f, 500.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera, player));
	GetLastGameObject()->SetTexture(enemy5);

	AddObjects(make_shared<Boss1>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(4050.0f, 100.0f), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), camera));

}

Level1::~Level1()
{

}

void Level1::BossBullets(std::shared_ptr<GameObject> enemy)
{
	glm::vec3 position = enemy->GetTransform()->GetPosition();
	glm::vec3 scale = enemy->GetTransform()->GetScale();

	AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(position.x - scale.x / 2.0f - 32.0f, position.y + scale.y/6), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), GetCamera(), GetEnemyBulletTex(), "boss"));
	AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(glm::vec2(position.x - scale.x / 2.0f - 32.0f, position.y - scale.y/6), glm::vec2(), 0.0f, false),
		make_shared<RigidbodyComponent>(), GetCamera(), GetEnemyBulletTex(), "boss"));
}
