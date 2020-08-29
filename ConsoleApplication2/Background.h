#pragma once
#include "structures.h"

class MeshComponent;
class TransformComponent;
class Texture2D;
class CameraComponent;

class Background
{
public:
	Background(std::shared_ptr<CameraComponent> camera);
	void Draw();
	void Update();

	std::shared_ptr<Texture2D> GetTexture() { return _texture; }
	void SetTexture(std::shared_ptr<Texture2D> texture) { _texture = texture; }
	MeshComponent* GetMesh() { return _mesh.get(); }
	TransformComponent* GetTransform() { return _transform.get(); }
	GLuint GetShader() { return ShaderProgram; }
	void SetShader(GLuint shader) { ShaderProgram = shader; }

private:
	std::shared_ptr<MeshComponent> _mesh;
	std::shared_ptr<TransformComponent> _transform;
	std::shared_ptr<Texture2D> _texture;
	std::shared_ptr<CameraComponent> _camera;
	GLuint ShaderProgram;
};

