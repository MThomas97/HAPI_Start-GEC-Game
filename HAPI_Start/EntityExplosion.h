#pragma once
#include "Entity.h"
class EntityExplosion : public Entity
{
public:
	EntityExplosion(std::string spriteID) : Entity(spriteID) { m_alive = false, health = 100; };
	~EntityExplosion();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return m_side; }

	void Spawn(const Vector2 &pos, int damageAmount);

private:
	eSide m_side{ eSide::eNeutral };
	Vector2 GetPos;
};

