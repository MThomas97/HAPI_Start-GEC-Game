#pragma once
#include "Entity.h"
class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) { lives = 3, curFrameX = 1;};

	~EntityPlayer();

	void Update(World &world, Visualisation &vis) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

private:
	float SetOnce{ true };
	DWORD lastTick{ 0 };
};

