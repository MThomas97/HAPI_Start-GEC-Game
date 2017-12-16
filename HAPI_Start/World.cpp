#include "World.h"
#include "Visualisation.h"
#include "EntityPlayer.h"
#include "EntityBackground.h"
#include "EntityScrollingBackground.h"
#include "EntityEnemy.h"
#include "EntityExplosion.h"
#include "EntityBullet.h"
#include "Vector2.h"
#include <HAPI_lib.h>
#include <algorithm>
#include <assert.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

constexpr DWORD kTickTime{ 50 };
constexpr int knumBullets{ 10 };

World::~World()
{
	delete m_vis;

	for (auto p : m_entity)
		delete p;
	
}

void World::run()
{
	m_vis = new Visualisation;

	if (!m_vis->initialise(screenWidth, screenHeight, "Intergalactic War"))
		return;

	if (!LoadLevel())
		return;

	Update();
}

bool World::LoadLevel()
{
	//Loads all the sprites

	if (!m_vis->CreateSprite("player", "Data\\idleSpriteV2.png", 4, 1))
		return false;

	if (!m_vis->CreateSprite("enemy", "Data\\player.png"))
		return false;

	if (!m_vis->CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", 5, 3))
		return false;

	if (!m_vis->CreateSprite("background", "Data\\FullStarBackground.png"))
		return false;
	
	if (!m_vis->CreateSprite("bullet", "Data//laserGreen.png"))
		return false;

	/*EntityExplosion *horse = new EntityExplosion("horse");
	m_entity.push_back(horse);

	horse->SetPosition(Vector2(200, 200));*/

	/*EntityBackground *newBackground = new EntityBackground("background");
	m_entity.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, 0));

	EntityScrollingBackground *newSecondBackground = new EntityScrollingBackground("background");
	m_entity.push_back(newSecondBackground);*/

	//newSecondBackground->SetPosition(Vector2(0, -800));

	
	//newPlayer->LoadRectangle(*m_vis);

	EntityPlayer *newPlayer = new EntityPlayer("player");
	m_entity.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(100, 300));

	EntityEnemy *enemy = new EntityEnemy("enemy");
	m_entity.push_back(enemy);

	enemy->SetPosition(Vector2(300, 300));
	
	

	/*for (int i = 0; i < knumBullets; i++)
	{
		EntityBullet *newBullet = new EntityBullet("bullet");
		m_entity.push_back(newBullet);
	}
*/

	

	return true;

}

void World::Update()
{

	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);

	DWORD lastTick{ 0 };

	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes

		PreviousTime = CurrentTime;
		CurrentTime = HAPI.GetTime();

		float dt = CurrentTime - PreviousTime;

		if (dt > 0.15f)
			dt = 0.15f;

		DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };
		
		if(TimeSinceLastTick >= kTickTime)
		{
			for (auto p : m_entity)
				p->Update(*m_vis, dt);

			lastTick = HAPI.GetTime();

			for (size_t i = 0; i < m_entity.size(); i++)
			{
				for (size_t j = i + 1; j < m_entity.size(); j++)
				{
					m_entity[i]->CheckCollision(*m_vis, *m_entity[j]);
				}
			}
			TimeSinceLastTick = 0;
		}
		
		float s = TimeSinceLastTick / (float)kTickTime;
		assert(s >= 0 && s <= 1.0f);

		m_vis->ClearToColour(HAPI.GetScreenPointer(), screenWidth, screenHeight, HAPI_TColour(0, 0, 0));

		for (auto p : m_entity)
			p->Render(*m_vis, s);
	}
}
