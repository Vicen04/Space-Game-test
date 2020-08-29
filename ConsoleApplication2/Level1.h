#pragma once
#include "GameScene.h"

class Level1 : public SceneBase
{
public:
	Level1(shared_ptr<Text> text, shared_ptr<CameraComponent> camera, shared_ptr<Player> player);
	~Level1();

	void BossBullets(std::shared_ptr<GameObject> enemy);
		
};

