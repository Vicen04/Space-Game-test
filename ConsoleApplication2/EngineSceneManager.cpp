#include "EngineSceneManager.h"
#include "Level1.h"
#include "MainMenu.h"
#include "Text.h"
#include "Player.h"
#include "MaterialAsset.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "CameraComponent.h"
#include "Highscores.h"
#include "Instructions1.h"


EngineSceneManager::EngineSceneManager()
{


}

EngineSceneManager::~EngineSceneManager()
{

}

void EngineSceneManager::Start()
{
	textManager = make_shared<Text>();
	camera = make_shared<CameraComponent>(1024.0f, 720.0f);
	currentScene = make_shared<MainMenu>(textManager, camera);
	current = MAINMENU;
}

void EngineSceneManager::StartGame()
{
	player = make_shared<Player>(make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f)),
		make_shared<TransformComponent>(),
		make_shared<RigidbodyComponent>(), camera);
	player->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	currentScene = make_shared<Level1>(textManager, camera, player);
	current = GAME;
}

void EngineSceneManager::Instructions()
{
	currentScene = make_shared<Instructions1>(textManager, camera);
	current = INSTRUCTIONS1;
}

void EngineSceneManager::Highscore()
{
	currentScene = make_shared<Highscores>(textManager, camera);
	current = HIGHSCORES;
}
void EngineSceneManager::Menu()
{
	currentScene = make_shared<MainMenu>(textManager, camera);
	current = MAINMENU;
}