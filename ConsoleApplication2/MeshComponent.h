#pragma once
#include <glm/vec2.hpp>   
#include <glm/vec3.hpp> 
#include <vector>
#include <memory>

class MaterialAsset;

typedef unsigned int GLuint;

struct Vertex
{
	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex)
	{
		_position = position; _normal = normal; _texCoord = tex;
	}

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec3 color)
	{
		_position = position; _normal = normal; _color = color;
	}

	Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 tex, glm::vec3 color)
	{
		_position = position; _normal = normal; _texCoord = tex; _color = color;
	}

	glm::vec3 _position;
	glm::vec3 _normal;
	glm::vec2 _texCoord;
	glm::vec3 _color;
};

class MeshComponent
{
public:
	MeshComponent(bool HasTexture, glm::vec2 ratio);
	MeshComponent(std::vector<Vertex> vertices, std::vector<GLuint> indices, bool hasTexture, bool HasColor);
	~MeshComponent();

	void SetPosition(std::vector<glm::vec3> position);
	void SetNormals(std::vector<glm::vec3> normal);
	void SetTexCoord(std::vector<glm::vec2> tex, bool hasTexture);
	void SetColor(std::vector<glm::vec3> color, bool hasColor);
	void SetIndices(std::vector<GLuint> indices);
	void SetMaterial(std::shared_ptr<MaterialAsset> material);

	std::vector<Vertex> GetVertices(){ return _vertex; }
	std::vector<GLuint> GetIndices(){ return _indices; }
	std::shared_ptr<MaterialAsset> GetMaterial() { return _material; }
	float GetRadius() { return _radius; }
	GLuint GetVertexArrayID() { return _vertexArrayID; };
	GLuint GetVertexBuffer() { return _vertexBuffer; };
	GLuint GetIndexBuffer() { return _indexBuffer; };

	bool HasTexture() { return _hasTexture; }
	bool HasColor() { return _hasColor; }

private:
	std::vector<Vertex> _vertex;
	std::vector<GLuint> _indices;
	std::shared_ptr<MaterialAsset> _material;
	bool _hasTexture = false;
	bool _hasColor = false;
	float _radius;
	GLuint _vertexArrayID, _indexBuffer, _vertexBuffer;
};

