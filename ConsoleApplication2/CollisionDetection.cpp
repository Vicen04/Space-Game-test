#include "CollisionDetection.h"
#include "GameObject.h"
#include "TransformComponent.h"

CollisionDetection::CollisionDetection()
{

}

CollisionDetection::~CollisionDetection()
{
	
}


bool CollisionDetection::Circle(GameObject* object1, GameObject* object2)
{
	glm::vec3 position1 = object1->GetTransform()->GetPosition();
	glm::vec3 position2 = object2->GetTransform()->GetPosition();

	glm::vec2 vector = glm::vec2((position1.x - position2.x), (position1.y - position2.y));
	
	double distance = sqrt((vector.x * vector.x) + (vector.y * vector.y));
	double combinedDistance = object1->GetCollisionRadius().radius + object2->GetCollisionRadius().radius;

	return distance < combinedDistance;

}

/*bool CollisionDetection::Box(Rect2D rect1, Rect2D rect2)
{
	if ((rect1.x < rect2.x + rect2.width) &&
		(rect2.x < rect1.x + rect1.width) &&
		(rect1.y < rect2.y + rect2.height) &&
		(rect2.y < rect1.y + rect1.height))
	{
		return true;
	}

	return false;
}*/