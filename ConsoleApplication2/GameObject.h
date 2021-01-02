#pragma once

#include <memory>
#include <string>
#include <map>
#include <glm/vec3.hpp> 

struct Circle2D
{
	float radius;

	Circle2D(float initialRad)
	{

		radius = initialRad;
	}
};

using namespace std;

class MeshComponent;
class RigidbodyComponent;
class TransformComponent;
class Texture2D;
class CameraComponent;
typedef unsigned int GLuint;

class GameObject
{
public:

	GameObject();
	GameObject(shared_ptr<MeshComponent> _mesh,	shared_ptr<TransformComponent> _transform, shared_ptr<RigidbodyComponent> _rigidBody, shared_ptr<CameraComponent> _camera);
	~GameObject();

	virtual void Update(float deltaTime) = 0;
	void Draw();
	virtual void Move() = 0;
	virtual void CheckIsOnScreen(glm::vec3 position, glm::vec3 camera) = 0;

	//this has to be here in order to get the right data for collision
	Circle2D GetCollisionRadius();
	//Rect2D GetCollisionBox();

	shared_ptr<Texture2D> GetTexture() { return _texture; }
	void SetTexture(shared_ptr<Texture2D> texture) { _texture = texture; }

	shared_ptr<MeshComponent> GetMesh() { return _mesh; }
	shared_ptr<TransformComponent> GetTransform() { return _transform; }
	shared_ptr<RigidbodyComponent> GetRigidBody() { return _rigidBody; }
	shared_ptr<CameraComponent> GetCamera() { return _camera; }
	GLuint GetShader() { return ShaderProgram; }
	bool GetUpdate() { return _update; }
	bool GetDestroy() { return _setToDestroy; }

	void SetMesh(shared_ptr<MeshComponent> mesh) { _mesh = mesh; }
	void SetTransform(shared_ptr<TransformComponent> transform) { _transform = transform; }
	void SetRigidBody(shared_ptr<RigidbodyComponent> rigidbody) { _rigidBody = rigidbody; }
	void SetCamera(shared_ptr<CameraComponent> camera) { _camera = camera; }
	void SetShader(GLuint shader) { ShaderProgram = shader; }
	string GetType() { return _type; }
	void SetType(string type) { _type = type; }
	void SetUpdate(bool update) { _update = update; }
	void SetDestroy(bool destroy) { _setToDestroy = destroy; }

private:
	shared_ptr<Texture2D> _texture;
	shared_ptr<MeshComponent> _mesh;
	shared_ptr<TransformComponent> _transform;
	shared_ptr<RigidbodyComponent> _rigidBody;
	shared_ptr<CameraComponent> _camera;
	GLuint ShaderProgram;
	string _type;
	bool _update = false, _setToDestroy = false;
};