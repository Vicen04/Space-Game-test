#include "GLUTCallbacks.h"
#include "EngineManager.h"
#include "Player.h"
#include "GameScene.h"
#include "MainMenu.h"

namespace GLUTCallbacks 
{
		unique_ptr<EngineManager> engineManager;
		shared_ptr<Player> player;
		shared_ptr<EngineSceneManager> scenes;

	void Init(EngineManager* newEngineManager)
	{
		engineManager.reset(newEngineManager);
		scenes = engineManager->GetSceneManager();
		scenes->Start();
	}

	void Display() 
	{ 

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw code
		
		engineManager->GetSceneManager()->GetCurrentScene()->Draw();

		glutSwapBuffers();
		glutPostRedisplay();
	}

	void Timer(int value)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME); 

		engineManager->Update((float)value/1000.0f); 

		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		if (updateTime > REFRESHRATE)
		glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, updateTime);
		else
			glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	}
	//'\x1b'
	void KeyboardKeyPressed(unsigned char key, int x, int y)
	{	

		switch (scenes->GetTypeScene())
		{
		case MAINMENU:

			if (key == 'W' || key == 'w')
			{
				static_cast<MainMenu*>(scenes->GetCurrentScene().get())->SelectSceneUp();
			}
			else if (key == 'S' || key == 's')
			{
				static_cast<MainMenu*>(scenes->GetCurrentScene().get())->SelectSceneDown();
			}
			else if (key == '\r')
			{
				switch (static_cast<MainMenu*>(scenes->GetCurrentScene().get())->GetSceneSelected())
				{
				case 0:
					scenes->StartGame();
					player = scenes->GetPlayer();
					break;
				case 1:
					scenes->Instructions();
					break;
				case 2:
					scenes->Highscore();
					break;
				case 3:
					glutDestroyWindow(glutGetWindow());
					break;
				}
			}
			break;

		case INSTRUCTIONS1:
			if (key == '\r')
			{
				scenes->Menu();
			}
			break;

		case HIGHSCORES:
			if (key == '\r' || key == '\x1b')
			{
				scenes->Menu();
			}
			break;

		case GAME:
			if (key == 'W' || key == 'w')
			{
				player->MoveUp(true);
				player->MoveDown(false);
			}
			else if (key == 'S' || key == 's')
			{
				player->MoveDown(true);
				player->MoveUp(false);
			}
			if (key == 'D' || key == 'd')
			{
				player->MoveRight(true);
				player->MoveLeft(false);
			}
			else if (key == 'A' || key == 'a')
			{
				player->MoveLeft(true);
				player->MoveRight(false);
			}
			break;
		}
		
	}

	void KeyboardKeyUp(unsigned char key, int x, int y)
	{
		switch (scenes->GetTypeScene())
		{
		case GAME:
			if (key == 'W' || key == 'w')
			{
				player->MoveUp(false);
			}
			else if (key == 'S' || key == 's')
			{
				player->MoveDown(false);
			}
			if (key == 'D' || key == 'd')
			{
				player->MoveRight(false);
			}
			else if (key == 'A' || key == 'a')
			{
				player->MoveLeft(false);
			}
		}
	}

	void MouseHandler(int button, int state, int x, int y)
	{
		switch (scenes->GetTypeScene())
		{
		case GAME:
			switch (button)
			{
			case GLUT_LEFT_BUTTON:
				if (state == GLUT_DOWN)
					player->SetShoot(true);
				else if (state == GLUT_UP)
					player->SetShoot(false);
				break;
			case GLUT_RIGHT_BUTTON:
				if (state == GLUT_DOWN)
					player->SetBomb(true);
				else if (state == GLUT_UP)
					player->SetBomb(false);
			}
		}
	}
}
