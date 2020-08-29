#pragma once
#include "GameObject.h"
class EnemyBase :
	public GameObject
{
public:
	EnemyBase(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~EnemyBase();

	virtual void Update(float time) = 0;
	virtual void Move() = 0;
	string GetEnemyType() { return _type; }
	void SetEnemyType(string type) { _type = type; }
	virtual void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);
	void TakeDamage() { _health--; }
	void SetHealth(int health) { _health = health; }
	 int GetHealth() { return _health; }
	void SetScore(unsigned int score) { _score = score; }
	unsigned int GetScore() { return _score; }
	float GetShootTime() { return _shootTime; }
	void SetShootTime(float time) { _shootTime = time; }
	virtual void ResetShootTime() { _shootTime = 2.0f; }

private:
	string _type;
	int _health;
	unsigned _score;
	float _shootTime = 0.5f;
};

