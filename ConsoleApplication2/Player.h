#pragma once
#include "GameObject.h"
#include <vector>


class Player : public GameObject
{
public:
	Player();
	Player(shared_ptr<MeshComponent> _mesh, shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);

	~Player();

	void Update(float time);
	void MoveLeft(bool left) { _left = left; }
	void MoveRight(bool right) { _right = right; }
	void MoveUp(bool up) { _up = up; }
	void MoveDown(bool down) { _down = down; }
	void Move();
	void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera);
	int GetLives() { return _lives; }
	int GetScore() { return _score; }
	int GetShield() { return _shield; }
	int GetBombs() { return _bombs; }
	int GetBullets() { return _bullets; }
	float GetShootCooldown() { return _timeToShoot; }
	float GetBombCooldown() { return _timeToBomb; }
	float GetInvincibility() { return _invincibility; }
	void ResetShootCooldown() { _timeToShoot = 2.0f; }
	void ResetBombCooldown() { _timeToBomb = 1.0f; }
	bool GetShoot() { return _shoot; }
	void SetShoot(bool shoot) { _shoot = shoot; }
	bool GetBomb() { return _bomb; }
	void SetBomb(bool bomb) { _bomb = bomb; }
	void BombUsed() { _bombs--; }
	void Reset();
	void TakeDamage();
	void AddScore(int score) { _score = _score + score; }
	void AddLives() { _lives++; }
	void AddBombs() { _bombs++; }
	void AddShield() { if (_shield < 3)_shield++; }
	void AddBullets() { if (_bullets < 5) { _bullets++; _shootSpeed = _shootSpeed + 0.25; } }
	void AddSpeed() { if (_speed < 2.0f) _speed = _speed + 0.25f; }

private:
	bool _left, _right, _up, _down, _shoot = false, _bomb = false;
	unsigned int _shield = 0, _bombs = 1, _lives = 3, _score = 0, _bullets = 1;
	float _timeToShoot = 0.0f, _timeToBomb = 0.0f, _speed = 1.0f, _shootSpeed = 1.0f, _invincibility = 0.0f;
	vector<glm::vec3> originalColor;
};

