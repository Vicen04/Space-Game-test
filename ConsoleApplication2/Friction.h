#pragma once

class GameObject;

class Friction 
{
public:
	Friction();
	void SetFriction(GameObject* gameobject);

private:
	float _frictionFactor;
};

