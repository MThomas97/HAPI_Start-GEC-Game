#include "EntityPlayer.h"
#include "Rectangle.h"
#include "EntityEnemy.h"

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::CheckCollision()
{
	m_playerRect = Rectangle(m_position.x, m_position.y);

	Rectangle CollisionRect(m_playerRect);
	

	if (CollisionRect.CheckCollision(tempRect) == true)
	{
		std::cout << "Collision detected!" << std::endl;
		m_position.x = std::max(0, std::min((int)m_position.x, 100 - m_playerRect.width() - 1));
		m_position.y = std::max(0, std::min((int)m_position.y, 100 - m_playerRect.height() - 1));
	}
	
}

void EntityPlayer::GetenemyRect(const Rectangle & other)
{
	tempRect = other;
}

void EntityPlayer::Update(float deltaTime)
{
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
		PrevTime = ElapsedTime;
		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			m_position.y -= m_speed * deltaTime;

		if (keyData.scanCode['S'])
			m_position.y += m_speed * deltaTime;

		if (keyData.scanCode['A'])
			m_position.x -= m_speed * deltaTime;

		if (keyData.scanCode['D'])
			m_position.x += m_speed * deltaTime;

		if (!(vect.x == 0 && vect.y == 0))
		{
			vect.x = m_speed * deltaTime * (vect.x / (vect.Length()));
			vect.y = m_speed *  deltaTime *(vect.y / (vect.Length()));

			m_position.x += vect.x;
			m_position.y += vect.y;
			
		}

		if (controllerData.isAttached)
		{

			if (Deadzone < LeftThumbX)
				m_position.x += m_speed * deltaTime;

			if (-Deadzone > LeftThumbX)
				m_position.x -= m_speed * deltaTime;

			if (-Deadzone > LeftThumbY)
				m_position.y += m_speed * deltaTime;

			if (Deadzone < LeftThumbY)
				m_position.y -= m_speed * deltaTime;

			if (!(vect.x == 0 && vect.y == 0))
			{
				vect.x = m_speed*(vect.x / (vect.Length()));
				vect.y = m_speed*(vect.y / (vect.Length()));

				m_position.x += vect.x;
				m_position.y += vect.y ;

			}
		}
		
}
