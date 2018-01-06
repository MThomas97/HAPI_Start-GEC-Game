#include "Entity.h"
#include "Visualisation.h"
#include "Rectangle.h"
Entity::~Entity()
{
}

void Entity::Render(Visualisation &vis, float s)
{
	if (!m_alive)
		return;

	Vector2 interPos{ m_oldPosition + (m_position - m_oldPosition) * s };



	if(NoAlpha)
		vis.RenderNoAlphaSprite(Spritename, (int)interPos.x, (int)interPos.y);

	if(!NoAlpha) 
	{
		vis.RenderSprite(Spritename, (int)interPos.x, (int)interPos.y, curFrameX, curFrameY);
	}
	
}

void Entity::CheckCollision(Visualisation & vis, Entity & other)
{
	if (!m_alive || !other.IsAlive())
		return;

	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

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

	if (thisRect.CheckCollision(otherRect))
	{
		TakeDamage(m_damageTaken);
		other.TakeDamage(m_damageTaken);
	}
}

bool Entity::IsEnemyOf(eSide a, eSide b)
{
	if (a == eSide::ePlayer && b == eSide::eEnemy || a == eSide::eEnemy && b == eSide::ePlayer)
		return true;

	if (a == eSide::eBullet && b == eSide::eEnemy || a == eSide::eEnemy && b == eSide::eBullet)
		return true;

	return false;
}

bool Entity::IsPickupOf(eSide a, eSide b)
{
	if (a == eSide::ePlayer && b == eSide::eNeutral || a == eSide::eNeutral && b == eSide::ePlayer)
		return true;

	return false;
}

void Entity::TakeDamage(int damageInflicted)
{
	health = health - damageInflicted;

	if (health <= 0)
	{
		lives = lives - 1;
		if(lives <= 0)
			m_alive = false;
		
		if(getSide() == eSide::eBullet)
			health = 1;
		else
		{
			health = 100;
		}
	}
}




