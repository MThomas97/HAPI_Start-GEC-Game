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


	Vector2 thisDir{ GetOldPosition() - GetPosition() };
	Vector2 otherDir{ other.GetOldPosition() = other.GetPosition() };

	float biggestLength = 1.0f / std::max(thisDir.Length(), otherDir.Length());

	thisDir = thisDir * biggestLength;
	otherDir = otherDir * biggestLength;

	Vector2 newThisPos{ GetPosition() };
	Vector2 newOtherPos{ other.GetPosition() };

	//do
	//{
	thisRect = Rectangle(thisRect);
	otherRect = Rectangle(otherRect);

	thisRect.left += width;
	thisRect.right -= width;
	thisRect.top += height;

	newThisPos = newThisPos + thisDir;
	newOtherPos = newOtherPos + otherDir;

	thisRect.Translate((int)newThisPos.x, (int)newThisPos.y);
	otherRect.Translate((int)newOtherPos.x, (int)newOtherPos.y);
	//} while ();

	//temp.x = m_position.x - w;

	//temp.y = m_position.y - h;

	if (thisRect.CheckCollision(otherRect))
	{
		
		SetBackPosition(oldPos);
		m_gravity -= 0.1f;
		isCollided = true;
		jumping = false;
	}

	//jumping = true;
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
	

	

	
	/*if (!isCollided)
	{
		pos.y += m_gravity;
		m_gravity += 0.1f;
	}*/
		

	if (m_gravity > 0.4f)
	{
		m_gravity = 0.4f;
	}

	//float jumpSpeed{ 10.0f };
	float acceleration{ 9.8f };


	//oldPos = m_position;
	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();
	const HAPI_TControllerData &controllerData = HAPI.GetControllerData(0);

	int LeftThumbX = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X];
	int LeftThumbY = controllerData.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y];
	int Deadzone = HK_GAMEPAD_LEFT_THUMB_DEADZONE;

	float ElapsedTime = HAPI.GetTime() - PrevTime;
	
	//pos += vel;

	//determines whether the player is on the ground
	const bool onground = pos.y >= 480;

	//vel += gravity;

			//Moves sprite with WASD keys
			if (keyData.scanCode['W'])
				pos.y -= m_speed;

				if (keyData.scanCode['S'])
					pos.y += m_speed;

				if (keyData.scanCode['A'])
					pos.x -= m_speed;

				if (keyData.scanCode['D'])
					pos.x += m_speed;

				if (jumping)
				{
					pos.y += jumpSpeed;
					jumpSpeed += 1;
					
					if (pos.y >= 300)
					{
						//pos.y = 300;
						jumping = false;
					}
				}
				else
				{
					if (keyData.scanCode[HK_SPACE])
					{
						jumping = true;
						jumpSpeed = -14;
					}
				}

				//if (keyData.scanCode[HK_SPACE])
				//{
				//	velocity = 7.0f;
				//		/*vel.y += jumpAccel * 2;
				//		jumpcounter = jumpframes;*/
				//	
				//	/*else if (jumpcounter > 0)
				//	{
				//		vel.y += jumpAccel;
				//		jumpcounter--;
				//	}*/
				//	pos.x += velocity.x;
				//	pos.y -= velocity.y;
				//}
				///*else {
				//	jumpcounter = 0;
				//}*/
				//velocity.y += m_gravity;
				//pos.x += velocity.x;
				//pos.y -= velocity.y;
			

			//velocity += acceleration * dt;
			//PlayerPosition += velocity * dt;

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


		if (HAPI.GetTime() - m_lastTimeUpdatedAnimation >= m_animationTime)
		{
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
			m_lastTimeUpdatedAnimation = HAPI.GetTime();
		}
}
