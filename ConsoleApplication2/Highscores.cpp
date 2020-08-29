#include "Highscores.h"
#include "CameraComponent.h"
#include "LightAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "Texture2D.h"
#include "Text.h"
#include "Background.h"
#include "MeshComponent.h"

Highscores::Highscores(shared_ptr<Text> text, shared_ptr<CameraComponent> camera) : Scene()
{
	_camera = camera;
	_camera->ResetCameraPosition();

	_light = std::make_shared<LightAsset>();
	_shader = std::make_shared<Shader>();
	_text = text;
	_background = make_shared<Background>(camera);
	_background->GetTexture()->Load("Textures/clouds.png");
	_background->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
}

Highscores::~Highscores()
{

}

void Highscores::Update(float time)
{
	_camera->UpdatePosition(0);
	_camera->UpdateMatrices();
	_background->Update();
}

void Highscores::Draw()
{
	if (_background->GetMesh()->HasTexture() && !_background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("TextureShader"));
	else if (!_background->GetMesh()->HasTexture() && _background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("ColorShader"));
	else if (_background->GetMesh()->HasTexture() && _background->GetMesh()->HasColor())
		_background->SetShader(_shader->GetShaderToInit("TextureColorShader"));

	_background->Draw();
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.position"), 1, glm::value_ptr(_light->GetPosition()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.ambient"), 1, glm::value_ptr(_light->GetAmbient()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.diffuse"), 1, glm::value_ptr(_light->GetDiffuse()));
	glUniform3fv(glGetUniformLocation(_background->GetShader(), "light.specular"), 1, glm::value_ptr(_light->GetSpecular()));

	glUniform3fv(glGetUniformLocation(_background->GetShader(), "viewPos"), 1, glm::value_ptr(_camera->GetCameraPosition()));

	int viewLoc = glGetUniformLocation(_background->GetShader(), "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetViewMatrix()));
	int projectionLoc = glGetUniformLocation(_background->GetShader(), "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetProjectionMatrix()));

	glDrawElements(GL_TRIANGLES, _background->GetMesh()->GetIndices().size(), GL_UNSIGNED_INT, 0);


	_text->RenderText(_shader->GetShaderToInit("TextShader"), "WORK IN PROGRESS ", 400.0f, 400.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));
	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Press ENTER to go back to the menu ", 325.0f, 350.0f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}