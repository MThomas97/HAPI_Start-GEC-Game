#pragma once

#include <vector>

class Visualisation;

class Entity;

class World
{
public:

	~World();

	void run();

	void Update();

	bool LoadLevel();

private:
	
	std::vector<Entity*> m_entity;

	Visualisation *m_vis{ nullptr };

	int screenWidth{ 600 };
	int screenHeight{ 800 };
};

