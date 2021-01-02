#pragma once
#include "GameObject.h"

//As the name says, this is the base class for all the enemies

class EnemyBase :
	public GameObject
{
public:

	//enemies move with the camera, the rest is used to be rendered properly and check the collisions
	EnemyBase(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~EnemyBase();

	//virtual functions for the child classes
	virtual void Update(float time) = 0;
	virtual void Move() = 0;

	//returns the enemy type
	string GetEnemyType() { return _type; }

	//sets the enmy type
	void SetEnemyType(string type) { _type = type; }

	// Checks if the enemy is on screen, enemies only update if they are completely inside the screen
	virtual void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);

	//enemy is hurt by the player
	void TakeDamage() { _health--; }

	//health of the enemy
	void SetHealth(int health) { _health = health; }
	 int GetHealth() { return _health; }

	 //score that the enemy gives to the player
	void SetScore(unsigned int score) { _score = score; }
	unsigned int GetScore() { return _score; }

	//Code related to the bullets shoot by the enemies, it varies depending on the enemy type
	float GetShootTime() { return _shootTime; }
	void SetShootTime(float time) { _shootTime = time; }
	virtual void ResetShootTime() { _shootTime = 2.0f; }

private:
	//type of enemy
	string _type;

	//health of the enemy
	int _health;

	unsigned _score;

	//Delay between bullets shot by the enemies
	float _shootTime = 0.5f;
};

