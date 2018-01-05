#include "EntityPlayer.h"
#include "Rectangle.h"
#include "Visualisation.h"
#include <string>

constexpr DWORD kClockTime{ 2000 };



EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::Update(World &world, Visualisation &vis, float dt)
{
	if (LoadOnce)
	{
		LoadSound();
		LoadOnce = false;
	}

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle ScreenRect(vis.GetScreenRect());

	thisRect.Translate(GetPosition().x, GetPosition().y);

	Vector2 pos{ GetPosition() };
	Vector2 vect;

	if (lives <= 0 && SetOnce)
	{
		
		HAPI_TSoundOptions loop(0.5f, true);
		HAPI.StopSound(instanceID, true);
		HAPI.PlaySound("Data\\Sounds\\death.ogg");
		HAPI.PlaySound("Data\\Sounds\\explosion.wav");
		world.FireExplosion(getSide(), Vector2(pos.x, pos.y), 10);
		SetOnce = false;
	}
	
	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();
	DWORD lastTick{ 0 };
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };

	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
	std::string stringScore = std::to_string(Score);
	HAPI.RenderText(90, 27, HAPI_TColour(0, 255, 0), stringScore, 30);
		
	//Moves sprite with WASD keys
	if (keyData.scanCode['W'] && thisRect.top > ScreenRect.top)
		pos.y -= m_speed;

	if (keyData.scanCode['S'] && thisRect.bottom < ScreenRect.bottom)
		pos.y += m_speed;

	if (keyData.scanCode['D'] && thisRect.right < ScreenRect.right)
	{
		pos.x += m_speed;
		curFrameX = 0;
	}

	if (keyData.scanCode['A'] && thisRect.left > ScreenRect.left)
	{
		pos.x -= m_speed;
		curFrameX = 2;
	}

	if (keyData.scanCode[HK_SPACE] && m_alive == true)
		world.FireBullet(getSide(), Vector2(pos.x, pos.y), 10);
					
	if (!keyData.scanCode['A'] && !keyData.scanCode['D'])
		curFrameX = 1;


	if (keyData.scanCode['A'] && keyData.scanCode['D'])
		curFrameX = 1;

	if (!(vect.x == 0 && vect.y == 0))
	{
		vect.x = m_speed * (vect.x / (vect.Length()));
		vect.y = m_speed * (vect.y / (vect.Length()));

		pos.x += vect.x;
		pos.y += vect.y;
	}

	if (controllerData.isAttached)
	{
		if (Deadzone < LeftThumbX)
				pos.x += m_speed;

		if (-Deadzone > LeftThumbX)
				pos.x -= m_speed;

		if (-Deadzone > LeftThumbY)
				pos.y += m_speed;

		if (Deadzone < LeftThumbY)
				pos.y -= m_speed;

		if (!(vect.x == 0 && vect.y == 0))
		{
			vect.x = m_speed *(vect.x / (vect.Length()));
			vect.y = m_speed *(vect.y / (vect.Length()));

			pos.x += vect.x;
			pos.y += vect.y;

		}
	}
			
	SetPosition(pos);
}

void EntityPlayer::LoadSound()
{
	HAPI_TSoundOptions loop(0.5f, true);
	HAPI.LoadSound("Data\\Sounds\\level1.ogg");
	HAPI.PlaySound("Data\\Sounds\\level1.ogg", loop, instanceID);
}
