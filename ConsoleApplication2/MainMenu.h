#pragma once
#include "Scene.h"
#include <vector>
#include <glm/vec3.hpp> 

class MainMenu :
	public Scene
{
public:
	MainMenu(std::shared_ptr<Text> _text, std::shared_ptr<CameraComponent> camera);
	~MainMenu();

	void Update(float time);
	void Draw();

	void SelectSceneUp();
	void SelectSceneDown();
	int GetSceneSelected() { return SceneSelected; }

private:
	std::shared_ptr<Text> _text, _textTitle;
	std::shared_ptr<Background> _background;
	std::shared_ptr<CameraComponent> _camera;
	std::shared_ptr<LightAsset> _light;
	std::shared_ptr<Shader> _shader;
	int SceneSelected = 0;

	std::vector<glm::vec3> colours;
};

