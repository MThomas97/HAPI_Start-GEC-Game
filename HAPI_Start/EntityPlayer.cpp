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
		m_gravity -= 0.1f;
		isCollided = true;
		
	}


	isCollided = false;
	//m_position = nextPos;
	/*CollisionRect.Translate(-GetPosition().x, -GetPosition().y);
	EnemyCollisionRect.Translate(-other.GetPosition().x, -other.GetPosition().y);*/
	//m_position.x = nextPos.x;
	//m_position.y = nextPos.y;
}

void EntityPlayer::Update(Visualisation &vis, float dt)
{
	//m_position = nextPos;
	
	Vector2 accel(Vector2(0.0, 0.0));
	
	Vector2 vel(0.0, 0.0);
	Vector2 gravity(0, 0.5f);


	Vector2 pos{ GetPosition() };

	Vector2 PlayerPosition{ GetPosition() };

	Vector2 PlayerOldPosition{ GetOldPosition() };

	Vector2 vect;

	//const float gravity{ 1 };
	int groundHeight{ 440 };
	Vector2 velocity;
	

	

	
	if (!isCollided)
	{
		pos.y += m_gravity;
		m_gravity += 0.1f;
	}
		

	if (m_gravity > 0.4f)
	{
		m_gravity = 0.4f;
	}

	float jumpSpeed{ 10.0f };
	float acceleration{ 9.8f };


	//oldPos = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
	pos += vel;

	//determines whether the player is on the ground
	const bool onground = pos.y >= 480;

	vel += gravity;

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
				{
					velocity = 3.0f;
					
						/*vel.y += jumpAccel * 2;
						jumpcounter = jumpframes;*/
					
					/*else if (jumpcounter > 0)
					{
						vel.y += jumpAccel;
						jumpcounter--;
					}*/
				}
				else {
					jumpcounter = 0;
				}
				

			

			velocity += acceleration * dt;
			PlayerPosition += velocity * dt;

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
		

		if (vel.y > max_fall)
			vel.y = max_fall;

		if (left)
		{
			vel.x -= RunAccel;
		}
		else if (right)
		{
			vel.x += RunAccel;
		}
		else {
			vel.x *= 0.9;
		}

		/*if (jump)
		{
			if (onground) 
			{
				vel.y += jumpAccel * 2;
				jumpcounter = jumpframes;
			}
			else if (jumpcounter > 0)
			{
				vel.y += jumpAccel;
				jumpcounter--;
			}
		}
		else {
			jumpcounter = 0;
		}*/

		/*if (pos.y > 480)
		{
			vel.y = 0;
			pos.y = 480;
		}

		if (pos.x < 16)
		{
			vel.x = 0;
			pos.x = 16;
		}
		else if (pos.x > 624)
		{
			vel.x = 0;
			pos.x = 624;
		}*/

		SetPosition(pos);
		//SetPosition(PlayerPosition);
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
