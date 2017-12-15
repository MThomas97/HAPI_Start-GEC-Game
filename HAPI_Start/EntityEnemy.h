#pragma once
#include "Entity.h"

class Rectangle;

class EntityEnemy : public Entity
{
public:
	EntityEnemy(std::string spriteID) : Entity(spriteID) {};
	~EntityEnemy();

	void Update(Visualisation &vis, float dt) override final;

	eSide getSide() const override final { return eSide::eEnemy; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

	Rectangle m_temp;
	Rectangle m_enemyRect;
	
private:
	//Rectangle m_enemyRect;

	
};

