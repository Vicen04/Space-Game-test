#include "GameScene.h"
#include "CameraComponent.h"
#include "LightAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "Texture2D.h"
#include "CollisionDetection.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "Background.h"
#include "Text.h"
#include "Bullet.h"
#include "Items.h"
#include "EnemyBase.h"
#include "Ally.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

SceneBase::SceneBase(shared_ptr<Text> text, shared_ptr<CameraComponent> camera, shared_ptr<Player> player): Scene()
{
	_camera = camera;
	_camera->ResetCameraPosition();
	_player = player;
	_light = std::make_shared<LightAsset>();
	_shader = std::make_shared<Shader>();
	_text = text;
	_collision = make_unique<CollisionDetection>();
	_playerbulletTex = make_shared<Texture2D>();
	_playerbulletTex->Load("Textures/player_bullet.png");
	_enemyBulletTex = make_shared<Texture2D>();
	_enemyBulletTex->Load("Textures/enemy_bullet.png");
	_shield = make_shared<Texture2D>();
	_shield->Load("Textures/shield_item.png");
	_life = make_shared<Texture2D>();
	_life->Load("Textures/lives_item.png");
	_bullet = make_shared<Texture2D>();
	_bullet->Load("Textures/bullet_item.png");
	_bomb = make_shared<Texture2D>();
	_bomb->Load("Textures/bomb_item.png");
	_speed = make_shared<Texture2D>();
	_speed->Load("Textures/speed_item.png");
	_bossBulletTex = make_shared<Texture2D>();
	_bossBulletTex->Load("Textures/boss_beam.png");
	_allyTex = make_shared<Texture2D>();
	_allyTex->Load("Textures/player_helper.png");
}


SceneBase::~SceneBase()
{
	
}

void SceneBase::SetBackground(string texture) 
{ 
	_background = make_shared<Background>(_camera);
	if (texture.find(".raw") != string::npos)
	    _background->GetTexture()->LoadRAW(texture.c_str(), 512, 512);
	else
		_background->GetTexture()->Load(texture.c_str());

	_background->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
}

void SceneBase::Update(float deltaTime)
{
	if (_player->GetBomb() && _player->GetBombCooldown() <= 0.0f && _player->GetBombs() > 0)
	{
		PlayerBomb();
		_player->BombUsed();
	}

	if (_player->GetBullets() > 3 && _allyTop.get() == nullptr || _player->GetBullets() > 4 && _allyBottom.get() == nullptr)
	{
		SpawnPlayerAllies();
	}

	if (_player->GetShoot() && _player->GetShootCooldown() <= 0.0f)
	{
		SpawnPlayerBullet();
	}

	_camera->UpdatePosition(deltaTime);
	_camera->UpdateMatrices();
	_background->Update();
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		if (_gameObjects.at(i)->GetDestroy())
		{
			_gameObjects.erase(_gameObjects.begin() + i);
			i--;
			continue;
		}
		_gameObjects.at(i)->Update(deltaTime);
		if (_gameObjects.at(i)->GetType() == "enemy")
			SpawnEnemyBullet(_gameObjects.at(i));

		if (_gameObjects.at(i)->GetType() != "bullet" && _gameObjects.at(i)->GetType() != "item")
		{
			for (auto& gameObject : _gameObjects)
			{
				if (gameObject != _gameObjects.at(i))
					CollisionManager(_gameObjects.at(i), gameObject);
			}
		}
	}
}

void SceneBase::Draw()
{
	if (_background->GetMesh()->HasTexture() && !_background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("TextureShader"));
	else if (!_background->GetMesh()->HasTexture() && _background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("ColorShader"));
	else if (_background->GetMesh()->HasTexture() && _background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("TextureColorShader"));

	_background->Draw();
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.position"), 1, glm::value_ptr(_light->GetPosition()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.ambient"), 1, glm::value_ptr(_light->GetAmbient()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.diffuse"), 1, glm::value_ptr(_light->GetDiffuse()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.specular"), 1, glm::value_ptr(_light->GetSpecular()));

	glUniform3fv(glGetUniformLocation(_background->GetShader(), "viewPos"), 1, glm::value_ptr(_camera->GetCameraPosition()));

	int viewLoc = glGetUniformLocation(_background->GetShader(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetViewMatrix()));
	int projectionLoc = glGetUniformLocation(_background->GetShader(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetProjectionMatrix()));

	glDrawElements(GL_TRIANGLES, _background->GetMesh()->GetIndices().size(), GL_UNSIGNED_INT, 0);

	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetUpdate())
		{
			if (gameObject->GetMesh()->HasTexture() && !gameObject->GetMesh()->HasColor())
				gameObject->SetShader(_shader->GetShaderToInit("TextureShader"));
			else if (!gameObject->GetMesh()->HasTexture() && gameObject->GetMesh()->HasColor())
				gameObject->SetShader(_shader->GetShaderToInit("ColorShader"));
			else if (gameObject->GetMesh()->HasTexture() && gameObject->GetMesh()->HasColor())
				gameObject->SetShader(_shader->GetShaderToInit("TextureColorShader"));

			gameObject->Draw();
			glUniform3fv(glGetUniformLocation(gameObject->GetShader(), "light.position"), 1, glm::value_ptr(_light->GetPosition()));
			glUniform3fv(glGetUniformLocation(gameObject->GetShader(), "light.ambient"), 1, glm::value_ptr(_light->GetAmbient()));
			glUniform3fv(glGetUniformLocation(gameObject->GetShader(), "light.diffuse"), 1, glm::value_ptr(_light->GetDiffuse()));
			glUniform3fv(glGetUniformLocation(gameObject->GetShader(), "light.specular"), 1, glm::value_ptr(_light->GetSpecular()));

			glUniform3fv(glGetUniformLocation(gameObject->GetShader(), "viewPos"), 1, glm::value_ptr(_camera->GetCameraPosition()));

			int viewLoc = glGetUniformLocation(gameObject->GetShader(), "view");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetViewMatrix()));
			int projectionLoc = glGetUniformLocation(gameObject->GetShader(), "projection");
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetProjectionMatrix()));

			glDrawElements(GL_TRIANGLES, gameObject->GetMesh()->GetIndices().size(), GL_UNSIGNED_INT, 0);
		}
	}

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Lives: " + std::to_string(_player->GetLives()), 25.0f, 690.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Score: " +  std::to_string(_player->GetScore()), 25.0f, 20.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Shield lvl: " + std::to_string(_player->GetShield()), 150.0f, 690.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Bombs: " + std::to_string(_player->GetBombs()), 325.0f, 690.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


}

void SceneBase::CollisionManager(shared_ptr<GameObject> object1, shared_ptr<GameObject> object2)
{
	if (_collision->Circle(object1.get(), object2.get()))
	{
		if (object1->GetType() == "player")
		{
			if (object2->GetType() == "item")
			{
				string type = static_cast<Items*>(object2.get())->GetItemType();
				if (type == "life")
				{
					_player->AddLives();
				}
				else if (type == "bullet")
				{
					_player->AddBullets();
				}
				else if (type == "bomb")
				{
					_player->AddBombs();
				}
				else if (type == "speed")
				{
					_player->AddSpeed();
				}
				else if (type == "shield")
				{
					_player->AddShield();
				}
				object2->SetDestroy(true);
			}
			else if (_player->GetInvincibility() <= 0.0f)
			{
			     if (object2->GetType() == "bullet")
		      	 {
				     string type = static_cast<Bullet*>(object2.get())->GetBulletType();
				     if (type != "player" )
				     {
					     _player->TakeDamage();
				     }
				     object2->SetDestroy(true);
			     }
			     else if (object2->GetType() == "enemy")
			     {
				      _player->TakeDamage();
			     }
			}
		}
		else if (object1->GetType() == "enemy")
		{
			if (object2->GetType() == "bullet")
			{
				string type = static_cast<Bullet*>(object2.get())->GetBulletType();
				if (type == "player")
				{
					EnemyBase* enemy = static_cast<EnemyBase*>(object1.get());
					enemy->TakeDamage();
					if (enemy->GetHealth() <= 0)
					{
						object1->SetDestroy(true);
						_player->AddScore(enemy->GetScore());
						SpawnItems(object1);
					}
					object2->SetDestroy(true);
				}
			}
		}
	}
}

void SceneBase::SpawnPlayerBullet()
{
	glm::vec3 position = _player->GetTransform()->GetPosition();
	glm::vec3 scale = _player->GetTransform()->GetScale();
	if (_player->GetBullets() == 1)
	{
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
	}
	else if (_player->GetBullets() == 2)
	{
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y + 10.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y - 10.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
	}
	else if (_player->GetBullets() == 3)
	{
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y + 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y - 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
	}
	else if (_player->GetBullets() == 4)
	{
		glm::vec3 position2 = _allyTop->GetTransform()->GetPosition();
		glm::vec3 scale2 = _allyTop->GetTransform()->GetScale();

		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y + 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y - 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position2.x + scale2.x / 2.0f + 16.0f, position2.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
	}
	else if (_player->GetBullets() == 5)
	{
		glm::vec3 position2 = _allyTop->GetTransform()->GetPosition();
		glm::vec3 scale2 = _allyTop->GetTransform()->GetScale();

		glm::vec3 position3 = _allyBottom->GetTransform()->GetPosition();
		glm::vec3 scale3 = _allyBottom->GetTransform()->GetScale();

		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y + 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x + scale.x / 2.0f + 16.0f, position.y - 30.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position2.x + scale2.x / 2.0f + 16.0f, position2.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
		AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position3.x + scale3.x / 2.0f + 16.0f, position3.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _playerbulletTex, "player"));
	}
	_player->ResetShootCooldown();

}

void SceneBase::SpawnPlayerAllies()
{
	glm::vec3 position = _player->GetTransform()->GetPosition();
	glm::vec3 scale = _player->GetTransform()->GetScale();

	if (_allyTop.get() == nullptr)
	{
		_allyTop = make_shared<Ally>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x, position.y +  45.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _player, _allyTex);
		AddObjects(_allyTop);
	}
	else if (_allyBottom.get() == nullptr)
	{
		_allyBottom = make_shared<Ally>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x, position.y - 45.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _player, _allyTex);
		AddObjects(_allyBottom);
	}
}

void SceneBase::SpawnEnemyBullet(std::shared_ptr<GameObject> enemy)
{
	EnemyBase* type = static_cast<EnemyBase*>(enemy.get());

	if (type->GetShootTime() <= 0.0f)
	{
		type->ResetShootTime();
		if (type->GetEnemyType() != "boss")
		{
			glm::vec3 position = enemy->GetTransform()->GetPosition();
			glm::vec3 scale = enemy->GetTransform()->GetScale();
			AddObjects(make_shared<Bullet>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - scale.x / 2.0f - 16.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _enemyBulletTex, "enemy"));
		}
		else
		{
			BossBullets(enemy);
		}
	}
}

void SceneBase::SpawnItems(std::shared_ptr<GameObject> enemy)
{
	string type = static_cast<EnemyBase*>(enemy.get())->GetEnemyType();

	int random = rand() % 100;

	if (random > 50 && type != "boss")
	{
		glm::vec3 position = enemy->GetTransform()->GetPosition();
		if (random > 95)
		{
			AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _life, "life"));
		}
		else if (random > 90)
		{
			AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _bomb, "bomb"));
		}
		else if (random > 80)
		{
			AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _shield, "shield"));
		}
		else if (random > 65)
		{
			AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _bullet, "bullet"));
		}
		else
		{
			AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
				make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
				make_shared<RigidbodyComponent>(), _camera, _speed, "speed"));
		}

	}
	else if (type == "boss")
	{
		glm::vec3 position = enemy->GetTransform()->GetPosition();
		AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x - 40.0f, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _life, "life"));
		AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x, position.y), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _bomb, "bomb"));
		AddObjects(make_shared<Items>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
			make_shared<TransformComponent>(glm::vec2(position.x -20.0f, position.y + 40.0f), glm::vec2(), 0.0f, false),
			make_shared<RigidbodyComponent>(), _camera, _shield, "shield"));
	}
	
}

void SceneBase::PlayerBomb()
{
	for (auto& gameObject : _gameObjects)
	{
		if (gameObject->GetType() != "item" && gameObject->GetType() != "player" && gameObject->GetUpdate())
		{
			if (gameObject->GetType() == "enemy")
			{
				EnemyBase* enemy = static_cast<EnemyBase*>(gameObject.get());
				if (enemy->GetEnemyType() == "boss")
				{
					enemy->SetHealth(enemy->GetHealth() - 10);
					if (enemy->GetHealth() < 0)
					{
						enemy->SetDestroy(true);
						SpawnItems(gameObject);
						_player->AddScore(enemy->GetScore());
					}
						
				}
				else
				{
					gameObject->SetDestroy(true);
					SpawnItems(gameObject);
					_player->AddScore(enemy->GetScore());
				}

				
			
			}
			else
				gameObject->SetDestroy(true);
		}
	}
}