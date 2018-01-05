#pragma once
#include "Entity.h"
#include <vector>
#include "Vector2.h"



class Visualisation;

class Entity;


class World
{
public:

	World(int width, int height, std::string name);

	~World();

	void FireBullet(eSide side, const Vector2 & pos, int damageAmount);

	void FireExplosion(eSide side, const Vector2 &pos, int damageAmount);

	void SpawnPickup(Vector2 &pos, int damageAmount);

	void SetRestart(bool reset) { IsFinished = reset; }

	void run();

private:
	
	void Update();

	bool LoadLevel();

	void ResetPositions();

	bool IsFinished{ false };

	std::vector<Entity*> m_entity;

	std::vector<Vector2> m_savePosition;

	Visualisation *m_vis{ nullptr };

	bool LoadOnce{ false };

	bool togglePause{ false };

	int toggletick{ 1 };

	int screenWidth{ 600 };
	int screenHeight{ 800 };

	size_t bulletStartIndex{ 3 };

	size_t StartIndex{ 3 };

	size_t ExplosionStartIndex{ 3 };

	Vector2 bulletPos;
};

