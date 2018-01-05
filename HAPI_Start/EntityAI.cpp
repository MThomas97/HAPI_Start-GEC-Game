#include "EntityAI.h"
#include "Visualisation.h"

EntityAI::~EntityAI()
{
}

void EntityAI::BackToPatrol()
{
	Vector2 pos{ GetPosition() };
	
	if (pos.x >= 400)
	{
		path = 1;
		
	}
	else if (pos.x <= 100)
	{
		path = 2;
		
	}
	if (pos.x >= 100 && pos.x <= 400 && path == 0) {
		path = 1;
		
	}
	
}

void EntityAI::Update(World &world, Visualisation &vis, float dt)
{
	Vector2 pos{ GetPosition() };

	//Set the start state of ai

	if (EntityDied)
	{
		m_alive = false;
		SetPosition(Vector2(250, -rand() % -1200 - 200));
		EntityDied = false;
		ResetPosition = true;
	}

	if (ResetPosition)
	{
		m_alive = false;
		SetPosition(Vector2(250, -rand() % -1200 - 200));
		ResetPosition = false;
	}
	else
	{
		m_alive = true;
		switch (path) {
		case 0:
			break;
		case 1:

			if (pos.x <= 50)
			{
				path = 2;
				break;
			}
			pos.x -= m_speed;
			pos.y += m_speed;
			break;

		case 2:
			if (pos.x >= 450)
			{
				path = 1;
				break;
			}
			pos.x += m_speed;
			pos.y += m_speed;
			break;
		case 3:
			BackToPatrol();
			break;
		}
			SetPosition(pos);
	}
	
		 

}

void EntityAI::CheckForPlayer(Visualisation &vis, Entity &other)
{
	

	/*if (!IsEnemyOf(getSide(), other.getSide()))
		return false;*/

	Vector2 otherDirPos{ other.GetOldPosition() - other.GetPosition() };
	Vector2 myPos{ GetPosition() };
	Vector2 otherPos{ other.GetPosition() };


	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));
	Rectangle AICollisionRect(thisRect);
	Rectangle OtherCollisionRect(otherRect);
	Rectangle ScreenRect(vis.GetScreenRect());
	OtherCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);

	AICollisionRect.Translate(GetPosition().x, GetPosition().y);

	if(AICollisionRect.top > ScreenRect.bottom)
	{ }

	if (OtherCollisionRect.right > AICollisionRect.left && OtherCollisionRect.left < AICollisionRect.right)
	{
		if (OtherCollisionRect.bottom > AICollisionRect.top && OtherCollisionRect.top < AICollisionRect.bottom)
		{
			alert = true;
			attack = 1;
		}
	}
	else
	{
		alert = false;
		attack = 0;
	}

	if (OtherCollisionRect.left > AICollisionRect.right)
	{
		if (OtherCollisionRect.bottom > AICollisionRect.top && OtherCollisionRect.top < AICollisionRect.bottom)
		{
			alert = true;
			attack = 2;
		}
	}
	else {
		alert = false;
		attack = 0;
	}
	//SetPosition(myPos);
	
}

void EntityAI::CheckCollision(Visualisation &vis, Entity &other)
{
	if (!m_alive)
		return;

	if (!other.IsAlive())
		return;

	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));
	Rectangle ScreenRect(vis.GetScreenRect());
	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

	CollisionRect.left += width;
	CollisionRect.right -= width;
	CollisionRect.top += height;
	Rectangle EnemyCollisionRect(otherRect);

	EnemyCollisionRect.Translate(other.GetPosition().x, other.GetPosition().y);

	CollisionRect.Translate(GetPosition().x, GetPosition().y);


	Vector2 thisDir{ GetOldPosition() - GetPosition() };
	Vector2 otherDir{ other.GetOldPosition() = other.GetPosition() };

	float biggestLength = 1.0f / std::max(thisDir.Length(), otherDir.Length());

	thisDir = thisDir * biggestLength;
	otherDir = otherDir * biggestLength;

	Vector2 newThisPos{ GetPosition() };
	Vector2 newOtherPos{ other.GetPosition() };

	thisRect = Rectangle(thisRect);
	otherRect = Rectangle(otherRect);

	thisRect.left += width;
	thisRect.right -= width;
	thisRect.top += height;

	newThisPos = newThisPos + thisDir;
	newOtherPos = newOtherPos + otherDir;

	thisRect.Translate((int)newThisPos.x, (int)newThisPos.y);
	otherRect.Translate((int)newOtherPos.x, (int)newOtherPos.y);

	if (thisRect.top > ScreenRect.bottom)
		ResetPosition = true;

	if (thisRect.CheckCollision(otherRect))
	{
		HAPI_TSoundOptions options(0.2f, false);
		HAPI.PlaySound("Data\\Sounds\\invaderkilled.wav", options);
		TakeDamage(m_damageTaken +40);
		other.TakeDamage(m_damageTaken+40);
		m_speed = m_speed + 1;
		m_alive = false;
		EntityDied = true;
	}
}
