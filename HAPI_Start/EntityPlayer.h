#pragma once
#include "Entity.h"

class Rectangle;

class Vector2;

class EntityPlayer : public Entity
{
public:
	EntityPlayer(std::string spriteID) : Entity(spriteID) {};

	~EntityPlayer();

	void Update(Visualisation &vis, float dt) override final;

	eSide getSide() const override final {return eSide::ePlayer; }

	void CheckCollision(Visualisation &vis, Entity &other) override final;

private:
	//Vector2 vect;


	//
	//Vector2 nextPos;

	//Vector2 newPos;

	//Vector2 oldPos;

	int PrevTime1 = 0;
	int PrevTime = 0;

	bool jumping{ false };
	float startY = 300;
	float jumpSpeed{ 0 };

	bool isCollided{ false };

	float m_gravity{ 0.1f };

	//const float gravity{ 9.0f };
	const float max_fall{ 5.0f };
	const float RunAccel{ 0.25f };
	const float maxRun{ 2.5f };
	const float max_air_time{ 1.2f };

	float timeInAir{ 0.0f };
	float jumpImpulseTime{ 0.2f };
	float jumpImpluseVel{ -10.0f };
	float jumpAccel{ -1.0f };
	const unsigned char jumpframes{ 10 };
	unsigned char jumpcounter{ 0 };

	bool left{ false };
	bool right{ false };
	bool jump{ false };
};

