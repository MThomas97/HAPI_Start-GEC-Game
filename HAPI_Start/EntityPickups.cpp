#include "EntityPickups.h"
#include "Visualisation.h"

EntityPickups::~EntityPickups()
{
}

void EntityPickups::Update(World &world, Visualisation & vis)
{
	Vector2 pos{ GetPosition() };
	
	Rectangle ScreenRect(vis.GetScreenRect());
	if (!m_alive)
		world.SpawnPickup(Vector2(pos.x, pos.y), 10);

	SetPosition(getPos);
}

void EntityPickups::CheckCollision(Visualisation & vis, Entity & other)
{
	if (!m_alive || !other.IsAlive())
		return;

	if (!IsPickupOf(getSide(), other.getSide()))
		return;

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

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
		HAPI.PlaySound("Data\\Sounds\\powerUp9.wav");
		other.AddScore(5);
		m_alive = false;
	}
}

void EntityPickups::Spawn(const Vector2 &pos, int damageAmount)
{

	getPos = pos;

	getPos.x = 20 * (float)(rand() % ((500 - 40) / 20)) + 20;
	getPos.y = 20 * (float)(rand() % ((700 - 40) / 20)) + 20;

	SetPosition(getPos);

	m_alive = true;

	
}
