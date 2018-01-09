#include "EntityPlayer.h"
#include "Visualisation.h"

constexpr DWORD kTickTime{ 300 };

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::Update(World &world, Visualisation &vis)
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };

	Rectangle thisRect(vis.GetRect(Spritename));
	
	Rectangle ScreenRect(vis.GetScreenRect());

	thisRect.Translate((int)GetPosition().x, (int)GetPosition().y);

	Vector2 pos{ GetPosition() };
	Vector2 vect;
	
	if (lives <= 0 && SetOnce)
	{
		HAPI.PlaySound("Data\\Sounds\\explosion.wav");
		world.FireExplosion(Vector2(pos.x, pos.y), 10);
		SetOnce = false;
	}
	
	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;
	
	Rectangle playerBulletRect(vis.GetRect(Spritename));
	playerBulletRect.Translate((int)GetPosition().x, (int)GetPosition().y);

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

	if (keyData.scanCode[HK_SPACE] && m_alive && TimeSinceLastTick >= kTickTime)
	{
		lastTick = HAPI.GetTime();
		world.FireBullet(Vector2((float)playerBulletRect.left + 45, (float)playerBulletRect.top - 33), 10);
		TimeSinceLastTick = 0;
	}
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
		if (Deadzone < LeftThumbX  && thisRect.right < ScreenRect.right)
		{
			pos.x += m_speed;
			curFrameX = 0;
		}
		if (-Deadzone > LeftThumbX && thisRect.left > ScreenRect.left)
		{
			pos.x -= m_speed;
			curFrameX = 2;
		}
		if (-Deadzone > LeftThumbY && thisRect.bottom < ScreenRect.bottom)
			pos.y += m_speed;

		if (Deadzone < LeftThumbY  && thisRect.top > ScreenRect.top)
			pos.y -= m_speed;

		if (-Deadzone < LeftThumbX && -Deadzone > LeftThumbX)
			curFrameX = 1;

		if (Deadzone < LeftThumbX && keyData.scanCode['D'])
			curFrameX = 1;

		if (controllerData.analogueButtons[HK_ANALOGUE_RIGHT_TRIGGER] && m_alive && TimeSinceLastTick >= kTickTime)
		{
			lastTick = HAPI.GetTime();
			world.FireBullet(Vector2((float)playerBulletRect.left + 45, (float)playerBulletRect.top - 33), 10);
			TimeSinceLastTick = 0;
		}
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
