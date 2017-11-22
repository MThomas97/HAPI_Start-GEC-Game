#include "EntityPlayer.h"
#include "WorldModel.h"

EntityPlayer::~EntityPlayer()
{
	delete m_visPlayer;
}

void EntityPlayer::Update()
{

	//Vector2 vect;
	m_visPlayer = new Visualisation;

	if (!m_visPlayer->CreateSprite("spriteID", "Data\\player.png"))
		return;

	static const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;

	float HorseElapsedTime = HAPI.GetTime() - PrevTime;
	//m_position.x = 0;
	if (PrevTime + 5 < ElapsedTime)
	{
		PrevTime = ElapsedTime;
		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			m_position.y -= MoveSpeed;

		if (keyData.scanCode['S'])
			m_position.y += MoveSpeed;

		if (keyData.scanCode['A'])
			m_position.x -= MoveSpeed;

		if (keyData.scanCode['D'])
			m_position.x += MoveSpeed;

		if (!(m_position.x == 0 && m_position.y == 0))
		{
			m_position.x = MoveSpeed*(m_position.x / (m_position.Length()));
			m_position.y = MoveSpeed*(m_position.y / (m_position.Length()));

			playerPosX += m_position.x;
			playerPosY += m_position.y;
			
		}

		if (controllerData.isAttached)
		{

			if (Deadzone < LeftThumbX)
				m_position.x += MoveSpeed;

			if (-Deadzone > LeftThumbX)
				m_position.x -= MoveSpeed;

			if (-Deadzone > LeftThumbY)
				m_position.y += MoveSpeed;

			if (Deadzone < LeftThumbY)
				m_position.y -= MoveSpeed;

			if (!(m_position.x == 0 && m_position.y == 0))
			{
				m_position.x = MoveSpeed*(m_position.x / (m_position.Length()));
				m_position.y = MoveSpeed*(m_position.y / (m_position.Length()));

				playerPosX += m_position.x;
				playerPosY += m_position.y;

			}
		}
	}

	Vector2 vect1;

	if (HorsePrevTime + 50 < HorseElapsedTime)
	{
		HorsePrevTime = HorseElapsedTime;
		
		vect1.x ++;

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

		if (!(vect1.x == 0 && vect1.y == 0))
		{
			vect1.x = 1*(vect1.x / (vect1.Length()));
			vect1.y = 1*(vect1.y / (vect1.Length()));

			curFrameX += vect1.x;
			curFrameY += vect1.y;

		}


	}
	
}

