#pragma once
#include "Entity.h"
#include <vector>
#include "Vector2.h"



class Visualisation;

class Entity;


class World
{
public:

	~World();

	void FireBullet(eSide side, const Vector2 & pos, int damageAmount);

	void run();

	

private:
	
	void Update();

	bool LoadLevel();

	std::vector<Entity*> m_entity;

	Visualisation *m_vis{ nullptr };

	int screenWidth{ 600 };
	int screenHeight{ 800 };

	size_t bulletStartIndex{ 1 };

	Vector2 bulletPos;
};

