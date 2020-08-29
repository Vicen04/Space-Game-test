#pragma once
class GameObject;

class CollisionDetection
{
public:
	CollisionDetection();
	~CollisionDetection();
	bool Circle(GameObject* object1, GameObject* object2);
	//bool Box(Rect2D rect1, Rect2D rect2);

};

