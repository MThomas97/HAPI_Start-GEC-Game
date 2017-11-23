#include "EntityPlayer.h"
#include "WorldModel.h"

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::Update()
{

	Vector2 vect;
	
	

	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;

	float HorseElapsedTime = HAPI.GetTime() - PrevTime;
	if (PrevTime + 20 < ElapsedTime)
	{
		PrevTime = ElapsedTime;
		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			vect.y -= MoveSpeed;

		if (keyData.scanCode['S'])
			vect.y += MoveSpeed;

		if (keyData.scanCode['A'])
			vect.x -= MoveSpeed;

		if (keyData.scanCode['D'])
			vect.x += MoveSpeed;

		if (!(vect.x == 0 && vect.y == 0))
		{
			vect.x = MoveSpeed*(vect.x / (vect.Length()));
			vect.y = MoveSpeed*(vect.y / (vect.Length()));

			m_position.x += vect.x;
			m_position.y += vect.y;
			
		}



		if (controllerData.isAttached)
		{

			if (Deadzone < LeftThumbX)
				vect.x += MoveSpeed;

			if (-Deadzone > LeftThumbX)
				vect.x -= MoveSpeed;

			if (-Deadzone > LeftThumbY)
				vect.y += MoveSpeed;

			if (Deadzone < LeftThumbY)
				vect.y -= MoveSpeed;

			if (!(vect.x == 0 && vect.y == 0))
			{
				vect.x = MoveSpeed*(vect.x / (vect.Length()));
				vect.y = MoveSpeed*(vect.y / (vect.Length()));

				m_position.x += vect.x;
				m_position.y += vect.y;

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
