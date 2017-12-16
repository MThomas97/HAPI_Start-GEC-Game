#pragma once
#include "Entity.h"

class Visualisation;

class EntityBullet : public Entity
{
public:
	EntityBullet(std::string spriteID) : Entity(spriteID) {};
	~EntityBullet();

	void Update(Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return m_side; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

	void Spawn();

private:
	eSide m_side{ eSide::eNeutral };
};

