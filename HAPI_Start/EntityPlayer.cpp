#include "EntityPlayer.h"
#include "Rectangle.h"
#include "EntityEnemy.h"
#include "Visualisation.h"

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::LoadRectangle(Visualisation &vis)
{
	m_playerRect = Rectangle(vis.GetRect("player"));
	m_enemyRect = Rectangle(vis.GetRect("enemy"));
}

void EntityPlayer::CheckCollision(Visualisation &vis, Entity &other)
{
	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Rectangle thisRect (vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.Spritename));

	//m_playerRect = Rectangle(sourceRect.width(), sourceRect.height());

	//m_enemyRect = Rectangle(destinationRect.width(), destinationRect.height());

	//Rectangle CollisionRect(m_playerRect);

	//Rectangle EnemyCollisionRect(m_enemyRect);

	Rectangle CollisionRect(thisRect);

	Rectangle EnemyCollisionRect(otherRect);

	int w{ thisRect.width() };

	thisRect.left += w / 10;

	thisRect.right += w / 10;

	w;

	int h{ thisRect.height() };

	thisRect.top += h / 10;

	thisRect.bottom += h / 10;

	EnemyCollisionRect.Translate(other.m_position.x, other.m_position.y);
	
	CollisionRect.Translate(m_position.x, m_position.y);

	Vector2 temp;

	temp.x = m_position.x - w;

	temp.y = m_position.y - h;

	if (CollisionRect.CheckCollision(EnemyCollisionRect) == true)
	{
		std::cout << "Collision detected!" << std::endl;
		//nextPos.x = temp.x;
		//nextPos.y = temp.y;
		nextPos = m_position;


		//nextPos.x = std::max(0, std::min((int)m_position.x, 1000 - thisRect.width() - 1));
		//nextPos.y = std::max(0, std::min((int)m_position.y, 1000 - thisRect.height() - 1));
		//CollisionRect.ClipTo(m_enemyRect);
		//return true;
	}

	
		
	//m_position = nextPos;
	CollisionRect.Translate(-m_position.x, -m_position.y);
	EnemyCollisionRect.Translate(-other.m_position.x, -other.m_position.y);
	m_position.x = nextPos.x;
	m_position.y = nextPos.y;
	//return false;
}

void EntityPlayer::GetenemyRect(const Rectangle & other)
{
	tempRect = other;
}

void EntityPlayer::Update(float deltaTime)
{
	//m_position = nextPos;
	//nextPos = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
		PrevTime = ElapsedTime;
		//Moves sprite with WASD keys
		if (keyData.scanCode['W'])
			nextPos.y -= m_speed * deltaTime;

		if (keyData.scanCode['S'])
			nextPos.y += m_speed * deltaTime;

		if (keyData.scanCode['A'])
			nextPos.x -= m_speed * deltaTime;

		if (keyData.scanCode['D'])
			nextPos.x += m_speed * deltaTime;

		if (!(vect.x == 0 && vect.y == 0))
		{
			vect.x = m_speed * deltaTime * (vect.x / (vect.Length()));
			vect.y = m_speed *  deltaTime *(vect.y / (vect.Length()));

			nextPos.x += vect.x;
			nextPos.y += vect.y;
			
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

		//CheckCollision(temp);
		
}
