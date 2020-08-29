#pragma once

class GameObject;

class Bounciness 
{
public:
	Bounciness();
	void SetBounciness(GameObject* gameobject);

private:
	float _bounciness;
};

