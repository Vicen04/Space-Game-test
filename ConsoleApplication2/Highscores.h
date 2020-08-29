#pragma once
#include "Scene.h"

class Highscores :
	public Scene
{
public:
	Highscores(std::shared_ptr<Text> _text, std::shared_ptr<CameraComponent> camera);
	~Highscores();

	void Update(float time);
	void Draw();

private:

	std::shared_ptr<Text> _text;
	std::shared_ptr<Background> _background;
	std::shared_ptr<CameraComponent> _camera;
	std::shared_ptr<LightAsset> _light;
	std::shared_ptr<Shader> _shader;
};

