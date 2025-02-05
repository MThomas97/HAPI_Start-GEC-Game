#pragma once
#include "Entity.h"
class EntityBullet : public Entity
{
public:
	EntityBullet(std::string spriteID) : Entity(spriteID) { m_alive = false, health = 1; };
	~EntityBullet();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return m_side; }

	void Spawn(const Vector2 &pos, int damageAmount);

	void CheckCollision(Visualisation & vis, Entity & other);

private:
	eSide m_side{ eSide::eNeutral };
	Vector2 GetPos;
	float IsCollided{ false };
};

