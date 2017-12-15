#include "EntityPlayer.h"
#include "Rectangle.h"
#include "Visualisation.h"

EntityPlayer::~EntityPlayer()
{
	
}

void EntityPlayer::CheckCollision(Visualisation &vis, Entity &other)
{
	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect (vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

	CollisionRect.left += width;
	CollisionRect.right -= width;
	CollisionRect.top += height;
	//CollisionRect.bottom -= height;
	Rectangle EnemyCollisionRect(otherRect);

	/*int w{ thisRect.width() };

	thisRect.left += w / 10;

	thisRect.right += w / 10;

	w;

	int h{ thisRect.height() };

	thisRect.top += h / 10;

	thisRect.bottom += h / 10;*/

	EnemyCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);
	
	CollisionRect.Translate(GetPosition().x, GetPosition().y);


	//temp.x = m_position.x - w;

	//temp.y = m_position.y - h;

	if (CollisionRect.CheckCollision(EnemyCollisionRect) == true)
	{
		//std::cout << "Collision detected!" << std::endl;
		//m_pos = oldPos;
		//m_position = m_oldPosition;
		SetBackPosition(oldPos);
		//nextPos.x = temp.x;
		//nextPos.y = temp.y;
		//GetPosition() = GetOldPosition();


		//nextPos.x = std::max(0, std::min((int)m_position.x, 1000 - thisRect.width() - 1));
		//nextPos.y = std::max(0, std::min((int)m_position.y, 1000 - thisRect.height() - 1));
		//CollisionRect.ClipTo(m_enemyRect);
		//return true;
	}


	
		
	//m_position = nextPos;
	/*CollisionRect.Translate(-GetPosition().x, -GetPosition().y);
	EnemyCollisionRect.Translate(-other.GetPosition().x, -other.GetPosition().y);*/
	//m_position.x = nextPos.x;
	//m_position.y = nextPos.y;
}

void EntityPlayer::Update(Visualisation &vis)
{
	//m_position = nextPos;
	
	Vector2 pos{ GetPosition() };

	Vector2 vect;

	const float gravity{ 1 };
	int groundHeight{ 440 };
	Vector2 velocity(Vector2(0, 0));

	float jumpSpeed{ 10.0f };

	//oldPos = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
		//PrevTime = ElapsedTime;
		if (HAPI.GetTime() - m_lastTimeUpdated >= m_time)
		{
			//Moves sprite with WASD keys
			if (keyData.scanCode['W'])
				pos.y -= m_speed;

			if (keyData.scanCode['S'])
				pos.y += m_speed;

			if (keyData.scanCode['A'])
				pos.x -= m_speed;

			if (keyData.scanCode['D'])
				pos.x += m_speed;

			if (keyData.scanCode[HK_SPACE])
				velocity.y = -jumpSpeed;
			else
			{
				velocity.x = 0;
			}

			if (GetPosition().y + 32 < groundHeight)
			{
				velocity.y += gravity;
			}

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
			m_lastTimeUpdated = HAPI.GetTime();
		}
		SetPosition(velocity);
		//SetPosition(pos);

		float HorseElapsedTime = HAPI.GetTime() - PrevTime;

		if (PrevTime + 150 < HorseElapsedTime)
		{
			PrevTime = HorseElapsedTime;

			curFrameX++;

			if (curFrameX >= vis.GetNumframesX(Spritename))
			{
				curFrameX = 0;

				curFrameY += 1;
			}

			if (curFrameY >= vis.GetNumframesY(Spritename))
			{
				curFrameY = 0;
				curFrameX = 0;

			}
		}
}
