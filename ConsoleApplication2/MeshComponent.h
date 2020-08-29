#pragma once
class MaterialAsset;
#include "structures.h"

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
	MeshComponent(vector<Vertex> vertices, vector<GLuint> indices, bool hasTexture, bool HasColor);
	~MeshComponent();

	void SetPosition(vector<glm::vec3> position);
	void SetNormals(vector<glm::vec3> normal);
	void SetTexCoord(vector<glm::vec2> tex, bool hasTexture);
	void SetColor(vector<glm::vec3> color, bool hasColor);
	void SetIndices(vector<GLuint> indices);
	void SetMaterial(shared_ptr<MaterialAsset> material);

	vector<Vertex> GetVertices(){ return _vertex; }
	vector<GLuint> GetIndices(){ return _indices; }
	shared_ptr<MaterialAsset> GetMaterial() { return _material; }
	float GetRadius() { return _radius; }
	GLuint GetVertexArrayID() { return _vertexArrayID; };
	GLuint GetVertexBuffer() { return _vertexBuffer; };
	GLuint GetIndexBuffer() { return _indexBuffer; };

	bool HasTexture() { return _hasTexture; }
	bool HasColor() { return _hasColor; }

private:
	vector<Vertex> _vertex;
	vector<GLuint> _indices;
	shared_ptr<MaterialAsset> _material;
	bool _hasTexture = false;
	bool _hasColor = false;
	float _radius;
	GLuint _vertexArrayID, _indexBuffer, _vertexBuffer;
};

