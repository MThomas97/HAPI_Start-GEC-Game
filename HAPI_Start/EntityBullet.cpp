#include "EntityBullet.h"
#include "Visualisation.h"

constexpr DWORD kClockTime{ 1000 };

EntityBullet::~EntityBullet()
{
}

void EntityBullet::Update(World &world, Visualisation &vis)
{
	Vector2 bulletPos{ GetPosition() };

	const Rectangle screenRect(vis.GetScreenRect());
	const Rectangle thisRect(vis.GetRect(Spritename));

	Rectangle TranslatethisRect(thisRect);

	TranslatethisRect.Translate((int)GetPosition().x, (int)GetPosition().y);

	if (TranslatethisRect.CompletelyOutside(screenRect))
		m_alive = false;

	if (!m_alive)
		m_side = eSide::eNeutral;

	if(m_alive)
		bulletPos.y -= m_speed;
		
	SetPosition(bulletPos);
}

void EntityBullet::CheckCollision(Visualisation & vis, Entity & other)
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
	
	if (thisRect.CheckCollision(otherRect) == true)
	{
		IsCollided = true;
	}
	else {
		IsCollided = false;
	}
}

void EntityBullet::Spawn(const Vector2 &pos, int damageAmount)
{
	m_side = eSide::eBullet;

	SetPosition(pos);
	m_alive = true;
}
