#include "EntityAI.h"
#include "Visualisation.h"
EntityAI::~EntityAI()
{
}

void EntityAI::Update(World &world, Visualisation &vis)
{
	Vector2 savePos;
	Vector2 pos{ GetPosition() };

	int a = -rand() % -1200 - 200;
	float r_float = (float)a;

	if (EntityDied)
	{
		world.FireExplosion(Vector2(pos.x, pos.y), 10);
	}
	if (EntityDied)
	{
		m_alive = false;
		SetPosition(Vector2((float)250, r_float));
		EntityDied = false;
		ResetPosition = true;
	}

	if (ResetPosition)
	{
		m_alive = false;
		SetPosition(Vector2((float)250, r_float));
		ResetPosition = false;
	}
	else
	{
		m_alive = true;
		//Set the start state of ai
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
		}
		SetPosition(pos);
	}
}

void EntityAI::CheckCollision(Visualisation &vis, Entity &other)
{
	if (!m_alive)
		return;

	if (!other.IsAlive())
		return;

	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 pos{ GetPosition() };

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));
	const Rectangle ScreenRect(vis.GetScreenRect());
	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

	CollisionRect.left += (int)width;
	CollisionRect.right -= (int)width;
	CollisionRect.top += (int)height;
	Rectangle EnemyCollisionRect(otherRect);

	EnemyCollisionRect.Translate((int)other.GetPosition().x, (int)other.GetPosition().y);

	CollisionRect.Translate((int)GetPosition().x, (int)GetPosition().y);

	Vector2 thisDir{ GetOldPosition() - GetPosition() };
	Vector2 otherDir{ other.GetOldPosition() = other.GetPosition() };

	float biggestLength = 1.0f / std::max(thisDir.Length(), otherDir.Length());

	thisDir = thisDir * biggestLength;
	otherDir = otherDir * biggestLength;

	Vector2 newThisPos{ GetPosition() };
	Vector2 newOtherPos{ other.GetPosition() };

	thisRect = Rectangle(thisRect);
	otherRect = Rectangle(otherRect);

	thisRect.left += (int)width;
	thisRect.right -= (int)width;
	thisRect.top += (int)height;

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
		TakeDamage(m_damageTaken + 40);
		other.TakeDamage(m_damageTaken + 40);

		if (other.getSide() == eSide::eBullet)
			other.AddScore(1);

		m_speed = m_speed + 1;
		m_alive = false;
		EntityDied = true;
	}
}
