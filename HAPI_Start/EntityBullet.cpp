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

	TranslatethisRect.Translate(GetPosition().x, GetPosition().y);

	if (TranslatethisRect.CompletelyOutside(screenRect))
		m_alive = false;

	if (health <= 0)
	{
		health = 1;
		
	}

	if (m_alive == false)
		m_side == eSide::eNeutral;

	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();
	DWORD lastTick{ 0 };
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };


	SetPosition(bulletPos);
	if (TimeSinceLastTick >= kClockTime)
	{
		bulletPos.y -= m_speed;
		
		lastTick = HAPI.GetTime();
		TimeSinceLastTick = 0;
	}

	SetPosition(bulletPos);
}

void EntityBullet::CheckCollision(Visualisation & vis, Entity & other)
{
}

void EntityBullet::Spawn(eSide side, const Vector2 &pos, int damageAmount)
{
	float PreviousTime = 0;
	float CurrentTime = HAPI.GetTime();
	DWORD lastTick{ 0 };
	DWORD TimeSinceLastTick{ HAPI.GetTime() - lastTick };
	//m_side = eSide::eNeutral;
	
	/*if (health >= 0)
	{
		m_side = eSide::eNeutral;
		health = 1;
	}*/
	
	GetPos = pos;
	m_side = side;
	if (TimeSinceLastTick >= kClockTime)
	{
		SetBackPosition(pos);
		SetPosition(pos);
		m_alive = true;
		lastTick = HAPI.GetTime();
		TimeSinceLastTick = 0;
	}
}
