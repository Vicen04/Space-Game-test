#pragma once
#include <memory>
class Scene;
class Text;
class Player;
class CameraComponent;

enum SceneSelection
{
	MAINMENU = 0,
	INSTRUCTIONS1 = 1,
	HIGHSCORES = 2,
	GAME = 3
};

class EngineSceneManager
{
public:
	EngineSceneManager();
	~EngineSceneManager();
	void Start();
	void Instructions();
	void Highscore();
	void Menu();
	void StartGame();

	std::shared_ptr<Player> GetPlayer() { return player; };

	std::shared_ptr<Scene> GetCurrentScene() { return currentScene; }

	SceneSelection GetTypeScene() { return current; }

private:
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<Text> textManager;
	std::shared_ptr<Player> player;
	std::shared_ptr<CameraComponent> camera;
	SceneSelection current = MAINMENU;
};

