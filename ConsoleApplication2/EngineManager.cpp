#include "EngineManager.h"
#include "GLUTCallbacks.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h> //freeglut library 
#include "GameScene.h"


void EngineManager::Start()
{

}

void EngineManager::Update(float deltaTime)
{
	if(engineSceneManager->GetCurrentScene() != nullptr)
		engineSceneManager->GetCurrentScene()->Update(deltaTime);
}

EngineManager::EngineManager(int argc, char* argv[])
{
	engineSceneManager = make_shared<EngineSceneManager>();

	InitWindow(argc, argv);
}

EngineManager::~EngineManager()
{

}

void EngineManager::InitWindow(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(300, 200);
	glutCreateWindow("Demonstration");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::KeyboardKeyPressed);
	glutKeyboardUpFunc(GLUTCallbacks::KeyboardKeyUp);
	glutMouseFunc(GLUTCallbacks::MouseHandler);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(err));
	}
	GLUTCallbacks::Init(this);
	glViewport(0, 0, 1024, 720);

	glEnable(GL_BLEND);

	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
}