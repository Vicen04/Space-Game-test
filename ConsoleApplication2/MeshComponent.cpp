#include "MeshComponent.h"
#include "MaterialAsset.h"

//creates a basic square / rectangle based on the ratio
MeshComponent::MeshComponent(bool texture, glm::vec2 ratio)
{
	glGenVertexArrays(1, &_vertexArrayID);
	glGenBuffers(1, &_vertexBuffer);
	glGenBuffers(1, &_indexBuffer);

	if (texture)
	{
		_vertex.push_back(Vertex(glm::vec3(-0.5f * ratio.x, -0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)));
		_vertex.push_back(Vertex(glm::vec3(-0.5f * ratio.x, 0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)));
		_vertex.push_back(Vertex(glm::vec3(0.5f * ratio.x, -0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)));
		_vertex.push_back(Vertex(glm::vec3(0.5f * ratio.x, 0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)));
		_hasTexture = true;
	}
	else
	{
		_vertex.push_back(Vertex(glm::vec3(-0.5f * ratio.x, -0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
		_vertex.push_back(Vertex(glm::vec3(-0.5f * ratio.x, 0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
		_vertex.push_back(Vertex(glm::vec3(0.5f * ratio.x, -0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
		_vertex.push_back(Vertex(glm::vec3(0.5f * ratio.x, 0.5f * ratio.y, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
		_hasColor = true;
	}

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(2);
	_indices.push_back(1);
	_indices.push_back(3);

	float maxX = INT_MIN, minX = INT_MAX, maxY = INT_MIN, minY = INT_MAX;
	for (int i = 0; i < _vertex.size(); i++)
	{
		maxX = fmax(_vertex.at(i)._position.x, maxX);
		maxY = fmax(_vertex.at(i)._position.y, maxY);

		minX = fmin(_vertex.at(i)._position.x, minX);
		minY = fmin(_vertex.at(i)._position.y, minY);
	}

	float radius1 = maxX - minX;
	float radius2 = maxY - minY;

	if (radius1 > radius2)
	{
		_radius = radius2;
	}
	else
		_radius = radius1;
}


MeshComponent::MeshComponent(vector<Vertex> vertices, vector<GLuint> indices, bool hasTexture, bool hasColor)
{
	_vertex = vertices;
	_indices = indices;
	_hasTexture = hasTexture;
	_hasColor = hasColor;
}

MeshComponent::~MeshComponent()
{
	glDeleteVertexArrays(1, &_vertexArrayID);
	glDeleteBuffers(1, &_vertexBuffer);
	glDeleteBuffers(1, &_indexBuffer);
	_vertex.clear();
	_indices.clear();
}

void MeshComponent::SetPosition(vector<glm::vec3> position)
{
	if (position.size() == _vertex.size())
	{
		for(int i = 0; i < _vertex.size(); i++)
		_vertex.at(i)._position = position.at(i);
	}
}
void MeshComponent::SetNormals(vector<glm::vec3> normal)
{ 
	if (normal.size() == _vertex.size())
	{
		for (int i = 0; i < _vertex.size(); i++)
			_vertex.at(i)._normal = normal.at(i);
	}
}
void MeshComponent::SetTexCoord(vector<glm::vec2> tex, bool hasTexture)
{
	if (tex.size() == _vertex.size())
	{
		for (int i = 0; i < _vertex.size(); i++)
			_vertex.at(i)._texCoord = tex.at(i);
	}
	_hasTexture = hasTexture;
}
void MeshComponent::SetColor(vector<glm::vec3> color, bool hasColor)
{ 
	if (color.size() == _vertex.size())
	{
		for (int i = 0; i < _vertex.size(); i++)
			_vertex.at(i)._color = color.at(i);
	}
	_hasColor = hasColor;
}
void MeshComponent::SetIndices(vector<GLuint> indices)
{
	if (indices.size() == _indices.size())
	{
		for (int i = 0; i < _vertex.size(); i++)
			_indices.at(i) = indices.at(i);
	}
}

void MeshComponent::SetMaterial(shared_ptr<MaterialAsset> material)
{
	_material = material;
}
