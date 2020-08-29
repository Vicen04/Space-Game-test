#include "GameObject.h"
#include "Texture2D.h"
#include "CollisionDetection.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "MaterialAsset.h"

GameObject::GameObject()
{	
	_mesh = make_shared<MeshComponent>(true, glm::vec2(1.0f, 1.0f));
	_transform = make_shared<TransformComponent>(glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::radians(0.0f), false);
	_rigidBody = make_shared<RigidbodyComponent>();
}

GameObject::GameObject(shared_ptr<MeshComponent> mesh, shared_ptr<TransformComponent> transform, shared_ptr<RigidbodyComponent> rigidBody, shared_ptr<CameraComponent> camera)
{
	_mesh = mesh;
	_transform = transform;
	_rigidBody = rigidBody;
	_camera = camera;
}

GameObject::~GameObject()
{

}

void GameObject::Draw()
{
	glBindVertexArray(_mesh->GetVertexArrayID());

	glBindBuffer(GL_ARRAY_BUFFER, _mesh->GetVertexBuffer());
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, _mesh->GetVertices().size() * sizeof(Vertex), &_mesh->GetVertices()[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->GetIndexBuffer());
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh->GetIndices().size() * sizeof(GL_UNSIGNED_INT), &_mesh->GetIndices()[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _mesh->GetVertexBuffer());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _mesh->GetIndexBuffer());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
			0,                  // attribute. Must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),  // stride
			(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::_normal));

	if (!_mesh->HasColor())
	{
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::_texCoord));
	}
	else if (!_mesh->HasTexture())
	{
		//color
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::_color));
	}
	else if (_mesh->HasTexture() && _mesh->HasColor())
	{
		// vertex texture coords and color
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::_texCoord));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::_color));
	}

	glUseProgram(ShaderProgram);

	glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "world"), 1, GL_FALSE, glm::value_ptr(_transform->GetWorldMatrix()));

	if (!_mesh->HasTexture())
	{
		glUniform3fv(glGetUniformLocation(ShaderProgram, "material.ambient"), 1, glm::value_ptr(_mesh->GetMaterial()->GetAmbient()));
		glUniform3fv(glGetUniformLocation(ShaderProgram, "material.diffuse"), 1, glm::value_ptr(_mesh->GetMaterial()->GetDiffuse()));
	}

	glUniform3fv(glGetUniformLocation(ShaderProgram, "material.specular"), 1, glm::value_ptr(_mesh->GetMaterial()->GetSpecular()));
	glUniform1f(glGetUniformLocation(ShaderProgram, "material.shininess"), _mesh->GetMaterial()->GetShininess());

	if (_mesh->HasTexture())
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
}


Circle2D GameObject::GetCollisionRadius()
{
	return Circle2D(_mesh->GetRadius() * _transform->GetScale().y/2.0f);
}

/*Rect2D GameObject::GetCollisionBox()
{
	return Rect2D(_position.x, _position.y, _texture->GetWidth(), _texture->GetHeight());
}*/

