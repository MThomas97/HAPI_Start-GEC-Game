#include "EntityPlayer.h"
#include "Rectangle.h"
#include "EntityEnemy.h"
#include "Visualisation.h"

EntityPlayer::~EntityPlayer()
{
	
}

bool EntityPlayer::CheckCollision(Vector2 nextPos, Rectangle sourceRect, Rectangle destinationRect)
{

	m_playerRect = Rectangle(sourceRect.width(), sourceRect.height());

	m_enemyRect = Rectangle(destinationRect.width(), destinationRect.height());

	Rectangle CollisionRect(m_playerRect);

	Rectangle EnemyCollisionRect(m_enemyRect);

	EnemyCollisionRect.Translate(400, 400);
	
	CollisionRect.Translate(m_position.x, m_position.y);

	
	if (CollisionRect.CheckCollision(m_enemyRect) == true)
	{
		std::cout << "Collision detected!" << std::endl;
		nextPos = m_position;
		/*m_position.x = std::max(1, std::min((int)m_position.x, 100 - m_playerRect.width() - 1));
		m_position.y = std::max(1, std::min((int)m_position.y, 100 - m_playerRect.height() - 1));*/
		//CollisionRect.ClipTo(m_enemyRect);
		return true;
	}
	CollisionRect.Translate(-m_position.x, -m_position.y);
	EnemyCollisionRect.Translate(-400, -400);
	m_position = nextPos;
	return false;
}

void EntityPlayer::GetenemyRect(const Rectangle & other)
{
	tempRect = other;
}

void EntityPlayer::Update(Visualisation &vis, float deltaTime)
{

	Vector2 temp;
	temp = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
		PrevTime = ElapsedTime;
		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			temp.y -= m_speed * deltaTime;

		if (keyData.scanCode['S'])
			temp.y += m_speed * deltaTime;

		if (keyData.scanCode['A'])
			temp.x -= m_speed * deltaTime;

		if (keyData.scanCode['D'])
			temp.x += m_speed * deltaTime;

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

		CheckCollision(temp, vis.GetRect("player"), vis.GetRect("enemy"));

		float HorseElapsedTime = HAPI.GetTime() - PrevTime;

		if (PrevTime + 150 < HorseElapsedTime)
		{
			PrevTime = HorseElapsedTime;

			curFrameX++;

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
		}
		
}
