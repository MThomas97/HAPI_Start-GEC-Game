#include "EntityBullet.h"
#include "World.h"
#include "Visualisation.h"

constexpr DWORD kClockTime{ 1000 };

EntityBullet::~EntityBullet()
{
}

void EntityBullet::Update(World &world, Visualisation &vis, float dt)
{
	Vector2 bulletPos{ GetPosition() };

	Rectangle screenRect(vis.GetScreenRect());
	Rectangle thisRect(vis.GetRect(Spritename));

	Rectangle TranslatethisRect(thisRect);

	static const HAPI_TKeyboardData &keyData = HAPI.GetKeyboardData();

	TranslatethisRect.Translate(GetPosition().x, GetPosition().y);

	

	if (IsCollided == true)
	{
		world.FireExplosion(getSide(), Vector2(bulletPos.x, bulletPos.y), 10);
		IsCollided = false;
	}
	if (TranslatethisRect.CompletelyOutside(screenRect))
		m_alive = false;

	if (m_alive == false)
		m_side == eSide::eNeutral;

	

	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();
	DWORD lastTick{ 0 };
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };


	//SetPosition(bulletPos);
	if (TimeSinceLastTick >= kClockTime)
	{
		if(m_alive)
			bulletPos.y -= m_speed;
		
		lastTick = HAPI.GetTime();
		TimeSinceLastTick = 0;
	}

	SetPosition(bulletPos);
}

void EntityBullet::CheckCollision(Visualisation & vis, Entity & other)
{
	/*if (!m_alive || !other.IsAlive())
		return;*/

	if (!IsEnemyOf(getSide(), other.getSide()))
		return;

	Vector2 oldPos{ GetOldPosition() };

	Rectangle thisRect(vis.GetRect(Spritename));
	Rectangle otherRect(vis.GetRect(other.GetSpritename()));

	Rectangle CollisionRect(thisRect);

	float width = thisRect.width() / 10.0f; //Reduces the size of the collider rectangle width by 10%

	float height = thisRect.height() / 10.0f; //Reduces the size of the collider rectangle height by 10%

	CollisionRect.left += width;
	CollisionRect.right -= width;
	CollisionRect.top += height;
	//CollisionRect.bottom -= height;
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
	
	if (thisRect.CheckCollision(otherRect) == true)
	{
		
		IsCollided = true;
		
	}
	else {
		IsCollided = false;
	}


	//isCollided = false;
}

void EntityBullet::Spawn(eSide side, const Vector2 &pos, int damageAmount)
{
	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();
	DWORD lastTick{ 0 };
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };
	
	//GetPos = pos;
	m_side = eSide::eBullet;
	if (TimeSinceLastTick >= kClockTime)
	{
		//SetBackPosition(pos);
		SetPosition(pos);
		m_alive = true;
		lastTick = HAPI.GetTime();
		TimeSinceLastTick = 0;
	}
}
