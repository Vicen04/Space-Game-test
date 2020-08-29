#pragma once

#include "Player.h"
#include "Scene.h"

class CollisionDetection;
class Ally;

class SceneBase: public Scene
{
public:

	SceneBase(shared_ptr<Text> _text, shared_ptr<CameraComponent> camera, shared_ptr<Player> player);
	~SceneBase();
	virtual void Update(float deltaTime);
	virtual void BossBullets(std::shared_ptr<GameObject> enemy) = 0;
	void Draw();

	void AddObjects(std::shared_ptr<GameObject> object) { _gameObjects.push_back(object); }
	void SetBackground(string texture); 
	void SpawnPlayerBullet();
	void SpawnPlayerAllies();
	void PlayerBomb();
	void SpawnEnemyBullet(std::shared_ptr<GameObject> enemy);
	void SpawnItems(std::shared_ptr<GameObject> enemy);
	void CollisionManager(std::shared_ptr<GameObject> object1, std::shared_ptr<GameObject> object2);
	vector<std::shared_ptr<GameObject>> GetGameObjects() { return _gameObjects; }
	std::shared_ptr<GameObject> GetLastGameObject() { if (_gameObjects.size() > 1)  return _gameObjects.at(_gameObjects.size() - 1); else return nullptr; }
	shared_ptr<CameraComponent> GetCamera() { return _camera; }
	LightAsset* GetLight() { return _light.get(); }
	Shader* GetShader() { return _shader.get(); }
	void SetPlayer(Player* player) { _player.reset(player); }
	shared_ptr<Player> GetPlayer() { return _player; }
	shared_ptr<Background> GetBackground() { return _background; };

	shared_ptr<Texture2D> GetEnemyBulletTex() { return _enemyBulletTex; }

private:
	vector< std::shared_ptr<GameObject>> _gameObjects;
	shared_ptr<Background> _background;
	shared_ptr<CameraComponent> _camera;
	shared_ptr<LightAsset> _light;
	shared_ptr<Shader> _shader;
	shared_ptr<Player> _player;
	shared_ptr<Text> _text;
	unique_ptr<CollisionDetection> _collision;
	shared_ptr<Texture2D> _playerbulletTex, _enemyBulletTex, _shield, _life, _bullet, _bomb, _speed, _bossBulletTex, _allyTex;
	shared_ptr<Ally> _allyTop, _allyBottom;
};

