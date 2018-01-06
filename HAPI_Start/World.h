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

	void FireExplosion(eSide side, const Vector2 &pos, int damageAmount);

	void SpawnPickup(Vector2 &pos, int damageAmount);

	void SetRestart(bool reset) { IsFinished = reset, GetIsFinished = reset; }

	bool GetRestart() { return GetIsFinished; }

	void run();

private:
	void Update();

	bool LoadLevel();

	bool IsFinished{ false };
	bool OnceSet{ true };
	bool CheckOnce{ true };
	bool GetIsFinished{ false };
	bool LoadOnce{ false };

	int deathID{ 1 };
	int instanceID{ 0 };
	int toggletick{ 1 };
	int controllerToggle{ 1 };
	int screenWidth{ 600 };
	int screenHeight{ 800 };
	int PlayerScore{ 0 };
	int SaveScore{ 0 };

	std::vector<Entity*> m_entity;

	Visualisation *m_vis{ nullptr };
	BYTE *iconPnter{ nullptr };
	size_t bulletStartIndex{ 11 };
	size_t StartIndex{ 11 };
	size_t ExplosionStartIndex{ 11 };
};

