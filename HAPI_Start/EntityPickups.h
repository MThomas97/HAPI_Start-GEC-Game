#pragma once
#include "Entity.h"
class EntityPickups : public Entity
{
public:
	EntityPickups(std::string spriteID) : Entity(spriteID) { m_alive = false, health = 1; };
	~EntityPickups();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final { return eSide::eNeutral; }

	void CheckCollision(Visualisation &vis, Entity &other);

	void Spawn(const Vector2 &pos, int damageAmount);

private:
	Vector2 getPos;
};

