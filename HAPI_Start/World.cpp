#include "World.h"
#include "Visualisation.h"
#include "EntityPlayer.h"
#include "UI.h"
#include "Vector2.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

World::~World()
{
	delete m_vis;
	
}

void World::run(int width, int height, std::string name)
{
	
}

bool World::LoadLevel()
{
	/*EntityPlayer *newEntity = new EntityPlayer("player");

	m_entity.push_back(newEntity);

	for (auto& p: newEntity)
		p->Update();*/

	return true;
}

void World::Update(int width, int height, std::string name)
{

	m_vis = new Visualisation;

	if (!m_vis->initialise(width, height, name))
		return;

	if (!LoadLevel())
		return;

	//Vector2 vect;
	//EntityPlayer playerEntity("player");

	//UI ui;


	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	//playerEntity.GraphicID("player");
	
//	if (!m_vis->CreateSprite("player", playerEntity.GetGraphicID()))
//		return;

	if (!m_vis->CreateSprite("starBackground", "Data\\FullStarBackground.png"))
		return;

	/*if (!visual.CreateSprite("player", "Data\\plyer.png"))
		return;*/

	//if (!m_vis->CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", playerEntity.numFramesX, playerEntity.numFramesY))
//		return;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		//const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

		m_vis->ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		
		m_vis->RenderNoAlphaSprite("starBackground", ScrollPosX, ScrollPosY);
		m_vis->RenderNoAlphaSprite("starBackground", SecondScrollPosX, SecondScrollPosY);
		//m_vis->RenderSprite("horse", 100, 100, playerEntity.curFrameX, playerEntity.curFrameY);
		//playerEntity.Update("player");
		//m_vis->RenderSprite("player", playerEntity.playerPosX, playerEntity.playerPosY);
		
		//playerEntity.Update();

		//int elapsedTime = HAPI.GetTime() - prevTime;
		//int playerElapsedTime = HAPI.GetTime() - playerPrevTime;
		int elapsedTime = HAPI.GetTime() - prevTime;
		ScrollPosY += 1;
		SecondScrollPosY += 1;

		/*if(prevTime +  1000/30 < elapsedTime)
		{
			prevTime = elapsedTime;

				curFrameX += 1;

			if (curFrameX >= numFramesX)
			{
				curFrameX = 0;
				curFrameY += 1;
			}

			if (curFrameY >= numFramesY)
			{
				curFrameY = 0;
				curFrameX = 0;
			}
		}*/

		//visual.ScrollingBackground(ScrollPosX, ScrollPosY, SecondScrollPosX, SecondScrollPosY); /////////GET WORKING

		if (ScrollPosY > m_vis->m_screenRect.bottom)
		{
			ScrollPosY = 0;
			SecondScrollPosY = -800;
		}

		

		//if (playerPrevTime + 10 < playerElapsedTime)
		//{
		//	playerPrevTime = playerElapsedTime;
		//	float playerSpeed = 5;

		//	//Moves sprite with WASD keys
		//	if (keyData.scanCode['W'])
		//		playerEntity.playerPosY -= playerSpeed;

		//	if (keyData.scanCode['S'])
		//		playerEntity.playerPosY += playerSpeed;

		//	if (keyData.scanCode['A'])
		//		playerEntity.playerPosX-= playerSpeed;

		//	if (keyData.scanCode['D'])
		//		playerEntity.playerPosX += playerSpeed;
		//}
		
		

		//if (playerEntity.playerPosY < height - 200 && playerEntity.playerPosX < width - 200 && playerEntity.playerPosY > 200 && playerEntity.playerPosX > 200)
		//{
		//	HAPI.SetControllerRumble(0, 40000, 40000);
		//}
		//else
		//{
		//	HAPI.SetControllerRumble(0, 0, 0);
		//}

		//if (controllerData.isAttached)
		//{
		//	//Gets the values of left thumb x, y and deadzone
		//	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
		//	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
		//	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

		//	float speed = 5;

		//	float translateX = 0;
		//	float translateY = 0;

		//	if (Deadzone < LeftThumbX)
		//		translateX +=speed;

		//	if (-Deadzone > LeftThumbX)
		//		translateX -= speed;

		//	if (-Deadzone > LeftThumbY)
		//		translateY += speed;

		//	if (Deadzone < LeftThumbY)
		//		translateY -= speed;

		//	if (!(translateX == 0 && translateY == 0))
		//	{

		//		float sqrRoot = sqrt((translateX*translateX) + (translateY*translateY));

		//		translateX = speed*(translateX / sqrRoot);
		//		translateY = speed*( translateY / sqrRoot);

		//		playerEntity.playerPosX += translateX;
		//		playerEntity.playerPosY += translateY;

		//		std::cout << LeftThumbX << LeftThumbY << std::endl;
		//	}
		//}

	
	}
}

void World::Render()
{
}
