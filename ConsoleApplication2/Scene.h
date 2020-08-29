#pragma once
#include <memory>

class LightAsset;
class Shader;
class CameraComponent;
class Background;
class Text;

class Scene
{
public:
	Scene();
	~Scene();

	virtual void Update(float time) = 0;
	virtual void Draw() = 0;
};

