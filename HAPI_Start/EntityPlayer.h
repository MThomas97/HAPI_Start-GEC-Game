#pragma once
#include "Entity.h"
#include "World.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) { lives = 3, curFrameX = 1;};

	~EntityPlayer();

	void Update(World &world, Visualisation &vis, float dt) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	void LoadSound();

	//void CheckCollision(Visualisation &vis, Entity &other) override final;

private:

	bool ClipToScreen{ false };
	float LoadOnce{ true };
	float SetOnce{ true };

	int instanceID;

	int PrevTime1 = 0;
	int PrevTime = 0;

	bool isCollided{ false };

	float playing = false;

	

};

