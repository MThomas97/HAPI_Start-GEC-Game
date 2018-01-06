#include "World.h"
#include "Visualisation.h"
#include "EntityPlayer.h"
#include "EntityBackground.h"
#include "EntityScrollingBackground.h"
#include "EntityExplosion.h"
#include "EntityBullet.h"
#include "EntityAI.h"
#include "EntityPlayerLives.h"
#include "EntityPickups.h"
#include "EntityAIFast.h"
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

constexpr DWORD kTickTime{ 20 };
constexpr int knumBullets{ 10 };
constexpr int knumExplosions{ 10 };
constexpr int knumPickups{ 5 };

World::~World()
{
	delete m_vis;

	for (auto p : m_entity)
		delete p;
	
}

void World::FireBullet(eSide side, const Vector2 &pos, int damageAmount)
{
	HAPI_TSoundOptions options(0.5f, false, 1.0f);

	for (size_t i = bulletStartIndex; i < bulletStartIndex + knumBullets; i++)
	{
		if (!m_entity[i]->IsAlive())
		{
			dynamic_cast<EntityBullet*>(m_entity[i])->Spawn(side, pos, damageAmount);
			HAPI.PlaySound("Data\\Sounds\\shoot.wav", options);
			break;
		}
	}
}

void World::SpawnPickup(Vector2 &pos, int damageAmount)
{
	for (size_t i = StartIndex + knumBullets + knumExplosions; i < bulletStartIndex + knumBullets + knumExplosions + knumPickups; i++)
	{
		if (!m_entity[i]->IsAlive())
		{
			dynamic_cast<EntityPickups*>(m_entity[i])->Spawn(pos, damageAmount);
			break;
		}
	}
}

void World::FireExplosion(eSide side, const Vector2 &pos, int damageAmount)
{
	for (size_t i = ExplosionStartIndex + knumBullets; i < ExplosionStartIndex + knumBullets + knumExplosions; i++)
	{
		if (!m_entity[i]->IsAlive())
		{
			dynamic_cast<EntityExplosion*>(m_entity[i])->Spawn(side, pos, damageAmount);
			break;
		}
	}
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

	if (!LoadOnce)
	{
		HAPI.LoadSound("Data\\Sounds\\level1.ogg");
		HAPI.LoadSound("Data\\Sounds\\death.ogg");
		HAPI.LoadSound("Data\\Sounds\\explosion.wav");
		HAPI.LoadSound("Data\\Sounds\\shoot.wav");
		HAPI.ChangeFontFromFile("Data\\Fonts\\kenvector_future_thin.ttf");

		if (!m_vis->CreateSprite("player", "Data\\playerMoveV3.png", 3, 1))
			return false;

		if (!m_vis->CreateSprite("enemyBlack", "Data\\SpaceShooter\\enemyBlack1.png"))
			return false;

		if (!m_vis->CreateSprite("enemyBlue", "Data\\SpaceShooter\\enemyBlue2.png"))
			return false;

		if (!m_vis->CreateSprite("enemyGreen", "Data\\SpaceShooter\\enemyGreen1.png"))
			return false;

		if (!m_vis->CreateSprite("enemyRed", "Data\\SpaceShooter\\enemyRed1.png"))
			return false;

		if (!m_vis->CreateSprite("horse", "Data\\HorseSpriteSheetWhite.png", 5, 3))
			return false;

		if (!m_vis->CreateSprite("background", "Data\\FullStarBackground.png"))
			return false;

		if (!m_vis->CreateSprite("bullet", "Data//laserRed.png"))
			return false;

		if (!m_vis->CreateSprite("lives", "Data\\SpaceShooter\\PlayerLivesV2.png", 1, 4))
			return false;

		if (!m_vis->CreateSprite("pickups", "Data\\SpaceShooter\\powerupRed_star.png"))
			return false;

		if (!m_vis->CreateSprite("ufoBlue", "Data\\SpaceShooter\\ufoBlue.png"))
			return false;

		if (!m_vis->CreateSprite("ufoGreen", "Data\\SpaceShooter\\ufoGreen.png"))
			return false;

		if (!m_vis->CreateSprite("ufoRed", "Data\\SpaceShooter\\ufoRed.png"))
			return false;

		if (!m_vis->CreateSprite("ufoYellow", "Data\\SpaceShooter\\ufoYellow.png"))
			return false;

		if (!m_vis->CreateSprite("explosion", "Data\\PlayerExplosion.png", 9, 9))
			return false;

		LoadOnce = true;
	}
	
	EntityBackground *newBackground = new EntityBackground("background");
	m_entity.push_back(newBackground);

	newBackground->SetPosition(Vector2(0, 0));

	EntityScrollingBackground *newSecondBackground = new EntityScrollingBackground("background");
	m_entity.push_back(newSecondBackground);

	newSecondBackground->SetPosition(Vector2(0, -800));

	EntityPlayer *newPlayer = new EntityPlayer("player");
	m_entity.push_back(newPlayer);

	newPlayer->SetPosition(Vector2(200, 300));

	EntityAI *newAI = new EntityAI("enemyBlack");
	m_entity.push_back(newAI);
	newAI->SetPosition(Vector2(250, -300));

	EntityAI *newAI2 = new EntityAI("enemyBlue");
	m_entity.push_back(newAI2);

	newAI2->SetPosition(Vector2(250, -600));

	EntityAI *newAI3 = new EntityAI("enemyGreen");
	m_entity.push_back(newAI3);

	newAI3->SetPosition(Vector2(250, -900));

	EntityAI *newAI4 = new EntityAI("enemyRed");
	m_entity.push_back(newAI4);

	newAI4->SetPosition(Vector2(250, -1200));

	EntityAIFast *fastAI = new EntityAIFast("ufoBlue");
	m_entity.push_back(fastAI);
	fastAI->SetPosition(Vector2(800, 100));

	EntityAIFast *fastAI2 = new EntityAIFast("ufoGreen");
	m_entity.push_back(fastAI2);
	fastAI2->SetPosition(Vector2(800, 300));

	EntityAIFast *fastAI3 = new EntityAIFast("ufoRed");
	m_entity.push_back(fastAI3);
	fastAI3->SetPosition(Vector2(800, 500));

	EntityAIFast *fastAI4 = new EntityAIFast("ufoYellow");
	m_entity.push_back(fastAI4);
	fastAI4->SetPosition(Vector2(800, 700));

	for (int i = 0; i < knumBullets; i++)
	{
		EntityBullet *newBullet = new EntityBullet("bullet");
		m_entity.push_back(newBullet);
	}

	for (int i = 0; i < knumExplosions; i++)
	{
		EntityExplosion *newExplosion = new EntityExplosion("explosion");
		m_entity.push_back(newExplosion);
	}

	for (int i = 0; i < knumPickups; i++)
	{
		EntityPickups *newPickup = new EntityPickups("pickups");
		m_entity.push_back(newPickup);
	}

	EntityPlayerLives *newLives = new EntityPlayerLives("lives");
	m_entity.push_back(newLives);

	newLives->SetPosition(Vector2(0, 45));
	return true;
}

void World::Update()
{
	//Sets the FPS counter on screen
	HAPI.SetShowFPS(true, 495, 0, HAPI_TColour::GREEN);

	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	HAPI_TSoundOptions loop(0.5f, true);

	DWORD lastTick{ 0 };

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes
		const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
		if (!IsFinished)
		{
			DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };

			if (TimeSinceLastTick >= kTickTime)
			{
				for (auto p : m_entity)
					p->Update(*this, *m_vis);

				lastTick = HAPI.GetTime();

				for (size_t i = 0; i < m_entity.size(); i++)
				{
					for (size_t j = i + 1; j < m_entity.size(); j++)
					{
						m_entity[j]->CheckCollision(*m_vis, *m_entity[i]);
						m_entity[i]->CheckCollision(*m_vis, *m_entity[j]);
					}
				}
				TimeSinceLastTick = 0;
			}

			float s = TimeSinceLastTick / (float)kTickTime;
			assert(s >= 0 && s <= 1.0f);

			HAPI.RenderText(0, -7, HAPI_TColour(255, 255, 255), "Score:", 45);

			m_vis->ClearToColour(HAPI.GetScreenPointer(), screenWidth, screenHeight, HAPI_TColour(0, 0, 0));

			for (auto p : m_entity)
				p->Render(*m_vis, s);

			if (m_entity[2]->GetLives() <= 0)
			{
				HAPI.RenderText(150, 300, HAPI_TColour(170, 1, 20), "GAME OVER!", 50);
				if (OnceSet)
				{
					HAPI_TSoundOptions loop(0.5f, true);
					HAPI.StopSound(instanceID);
					HAPI.PlaySound("Data\\Sounds\\death.ogg", loop, deathID);
					OnceSet = false;
				}
			}
			if (m_entity[2]->GetLives() >= 0 && CheckOnce)
			{
				HAPI_TSoundOptions loop(0.5f, true);
				HAPI.PlaySound("Data\\Sounds\\level1.ogg", loop, instanceID);
				CheckOnce = false;
			}

			for (int i = 0; i < m_entity.size(); i++)
				PlayerScore = PlayerScore + m_entity[i]->GetScore();

			std::string stringScore = std::to_string(PlayerScore);
			HAPI.RenderText(175, -11, HAPI_TColour(255, 255, 255), stringScore, 50);
			SaveScore = PlayerScore;
		}
		
		if (!keyData.scanCode['P'])
			toggletick = 1;

		if (keyData.scanCode['P'] && toggletick == 1 && m_entity[2]->IsAlive())
		{
			HAPI_TSoundOptions loop(0.5f, true);
			toggletick = 0;
			if (IsFinished)
				IsFinished = false;
			else if (!IsFinished)
				IsFinished = true;
		}

		if (!controllerData.digitalButtons[HK_DIGITAL_START])
			controllerToggle = 1;

		if (controllerData.digitalButtons[HK_DIGITAL_START] && controllerToggle == 1 && m_entity[2]->IsAlive())
		{
			HAPI_TSoundOptions loop(0.5f, true);
			controllerToggle = 0;
			if (IsFinished)
				IsFinished = false;
			else if (!IsFinished)
				IsFinished = true;
		}

		if (keyData.scanCode['R'] && !m_entity[2]->IsAlive() || controllerData.digitalButtons[HK_DIGITAL_A] && !m_entity[2]->IsAlive())
		{
			HAPI.StopSound(deathID);
			CheckOnce = true;
			OnceSet = true;
			IsFinished = true;
			GetIsFinished = IsFinished;
			for (auto p = m_entity.begin(); p != m_entity.end(); ++p)
				delete *p;
			
			m_entity.clear();
			m_vis->ClearToColour(HAPI.GetScreenPointer(), screenWidth, screenHeight, HAPI_TColour(0, 0, 0));
			IsFinished = false;
			LoadLevel();
		}

		if (IsFinished)
		{
			m_entity[2]->SetPaused(true);
			std::string stringScore = std::to_string(SaveScore);
			HAPI.RenderText(0, -7, HAPI_TColour(255, 255, 255), "Score:", 45);
			HAPI.RenderText(175, -11, HAPI_TColour(255, 255, 255), stringScore, 50);
			HAPI.RenderText(200, 300, HAPI_TColour(9, 4, 106), "Paused", 50);
		}
		PlayerScore = 0;
	}
}
