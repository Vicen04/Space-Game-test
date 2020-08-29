#pragma once
#include "Scene.h"
#include <vector>

class Instructions1 :
	public Scene
{
public:
	Instructions1(std::shared_ptr<Text> _text, std::shared_ptr<CameraComponent> camera);
	~Instructions1();

	void Update(float time);
	void Draw();

private:
	std::shared_ptr<Text> _text;
	std::vector<std::shared_ptr<Background>> _background;
	std::shared_ptr<CameraComponent> _camera;
	std::shared_ptr<LightAsset> _light;
	std::shared_ptr<Shader> _shader;
};

