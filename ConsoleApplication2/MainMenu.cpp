#include "MainMenu.h"
#include "CameraComponent.h"
#include "LightAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "Texture2D.h"
#include "Text.h"
#include "Background.h"
#include "MeshComponent.h"

MainMenu::MainMenu(shared_ptr<Text> text, shared_ptr<CameraComponent> camera) : Scene()
{
	_camera = camera;
	_camera->ResetCameraPosition();
	_textTitle = std::make_shared<Text>("Fonts/PaladinsSemiItalic-Y6Yo.otf");
	_light = std::make_shared<LightAsset>();
	_shader = std::make_shared<Shader>();
	_text = text;
	_background = make_shared<Background>(camera);
	_background->GetTexture()->Load("Textures/menu.png");
	_background->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));

	colours.push_back(glm::vec3(0.7f, 0.3f, 0.2f));
	colours.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colours.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	colours.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
}

MainMenu::~MainMenu()
{

}

void MainMenu::Update(float time)
{
	_camera->UpdatePosition(0);
	_camera->UpdateMatrices();
	_background->Update();
}

void MainMenu::Draw()
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

	_textTitle->RenderText(_shader->GetShaderToInit("TextShader"), "Space game ", 80.0f, 600.0f, 1.8f, glm::vec3(0.6f, 0.8f, 1.0f));

	_textTitle->RenderText(_shader->GetShaderToInit("TextShader"), "demo", 320.0f, 500.0f, 1.8f, glm::vec3(0.6f, 0.8f, 1.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Start Game ", 350.0f, 400.0f, 1.5f, colours.at(0));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Instructions " , 350.0f, 325.0f, 1.5f, colours.at(1));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Highscores", 350.0f, 250.0f, 1.5f, colours.at(2));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Exit", 450.0f, 175.0f, 1.5f, colours.at(3));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void MainMenu::SelectSceneDown()
{
	colours.at(SceneSelected) = glm::vec3(1.0f, 1.0f, 1.0f);
	SceneSelected++;
	if (SceneSelected > 3)
		SceneSelected = 0;
	colours.at(SceneSelected) = glm::vec3(0.7f, 0.3f, 0.2f);
}

void MainMenu::SelectSceneUp()
{
	colours.at(SceneSelected) = glm::vec3(1.0f, 1.0f, 1.0f);
	SceneSelected--;
	if (SceneSelected < 0)
		SceneSelected = 3;
	colours.at(SceneSelected) = glm::vec3(0.7f, 0.3f, 0.2f);
}
