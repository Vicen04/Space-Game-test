#include "Instructions1.h"
#include "CameraComponent.h"
#include "LightAsset.h"
#include "ShaderAsset.h"
#include "MaterialAsset.h"
#include "Texture2D.h"
#include "Text.h"
#include "Background.h"
#include "MeshComponent.h"
#include "TransformComponent.h"

Instructions1::Instructions1(shared_ptr<Text> text, shared_ptr<CameraComponent> camera) : Scene()
{
	_camera = camera;
	_camera->ResetCameraPosition();

	_light = std::make_shared<LightAsset>();
	_shader = std::make_shared<Shader>();
	_text = text;
	_background.push_back(make_shared<Background>(camera));
	_background.at(0)->GetTexture()->Load("Textures/clouds.png");
	_background.at(0)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.push_back(make_shared<Background>(camera));
	_background.at(1)->GetTexture()->Load("Textures/shield_item.png");
	_background.at(1)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.at(1)->GetTransform()->SetPosition(glm::vec3(45.0f, 210.0f, 0.0f));
	_background.at(1)->GetTransform()->SetScale(glm::vec3(50.0f, 50.0f, 1.0f));
	_background.push_back(make_shared<Background>(camera));
	_background.at(2)->GetTexture()->Load("Textures/bomb_item.png");
	_background.at(2)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.at(2)->GetTransform()->SetPosition(glm::vec3(45.0f, 280.0f, 0.0f));
	_background.at(2)->GetTransform()->SetScale(glm::vec3(50.0f, 50.0f, 1.0f));
	_background.push_back(make_shared<Background>(camera));
	_background.at(3)->GetTexture()->Load("Textures/lives_item.png");
	_background.at(3)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.at(3)->GetTransform()->SetPosition(glm::vec3(45.0f, 350.0f, 0.0f));
	_background.at(3)->GetTransform()->SetScale(glm::vec3(50.0f, 50.0f, 1.0f));
	_background.push_back(make_shared<Background>(camera));
	_background.at(4)->GetTexture()->Load("Textures/speed_item.png");
	_background.at(4)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.at(4)->GetTransform()->SetPosition(glm::vec3(45.0f, 420.0f, 0.0f));
	_background.at(4)->GetTransform()->SetScale(glm::vec3(50.0f, 50.0f, 1.0f));
	_background.push_back(make_shared<Background>(camera));
	_background.at(5)->GetTexture()->Load("Textures/bullet_item.png");
	_background.at(5)->GetMesh()->SetMaterial(make_shared<MaterialAsset>(true));
	_background.at(5)->GetTransform()->SetPosition(glm::vec3(45.0f, 140.0f, 0.0f));
	_background.at(5)->GetTransform()->SetScale(glm::vec3(50.0f, 50.0f, 1.0f));
}

Instructions1::~Instructions1()
{

}

void Instructions1::Update(float time)
{
	_camera->UpdatePosition(0);
	_camera->UpdateMatrices();
	for (auto& background : _background)
	{
		background->Update();
	}
}

void Instructions1::Draw()
{		
	for (auto& background : _background)
	{
		background->SetShader(_shader->GetShaderToInit("TextureShader"));

		background->Draw();
		glUniform3fv(glGetUniformLocation(background->GetShader(), "light.position"), 1, glm::value_ptr(_light->GetPosition()));
		glUniform3fv(glGetUniformLocation(background->GetShader(), "light.ambient"), 1, glm::value_ptr(_light->GetAmbient()));
		glUniform3fv(glGetUniformLocation(background->GetShader(), "light.diffuse"), 1, glm::value_ptr(_light->GetDiffuse()));
		glUniform3fv(glGetUniformLocation(background->GetShader(), "light.specular"), 1, glm::value_ptr(_light->GetSpecular()));

		glUniform3fv(glGetUniformLocation(background->GetShader(), "viewPos"), 1, glm::value_ptr(_camera->GetCameraPosition()));

		int viewLoc = glGetUniformLocation(background->GetShader(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetViewMatrix()));
		int projectionLoc = glGetUniformLocation(background->GetShader(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(_camera->GetProjectionMatrix()));

		glDrawElements(GL_TRIANGLES, background->GetMesh()->GetIndices().size(), GL_UNSIGNED_INT, 0);
	}
	

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "W: move the character up", 25.0f, 690.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "S: move the character down", 25.0f, 650.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "D: move the character right ", 25.0f, 610.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "A: move the character left ", 25.0f, 570.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "LEFT CLICK to shoot", 25.0f, 530.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "RIGHT CLICK to use a bomb, a bomb will wipe out all the enemies on the screen", 25.0f, 480.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "SPEED: collectable that increases the speed of the spaceship, you can collect up to 5", 80.0f, 410.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "LIFE: collectable that increases the lives of the spaceship", 80.0f, 340.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "BOMB: collectable that increases the bomb count of the spaceship", 80.0f, 270.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "SHIELD: collectable that acts as a life, you can collect up to 3", 80.0f, 200.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "BULLET: collectable that increases the shoot speed and bullet spawn, you can collect up to 5", 80.0f, 130.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));

	_text->RenderText(_shader->GetShaderToInit("TextShader"), "Press ENTER to go back to the main menu", 320.0f, 30.0f, 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}