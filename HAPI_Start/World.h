#pragma once

#include <vector>

class Visualisation;

class Entity;

class World
{
public:

	~World();

	void run();

private:
	
	void Update();

	bool LoadLevel();

	std::vector<Entity*> m_entity;

	Visualisation *m_vis{ nullptr };

	int screenWidth{ 600 };
	int screenHeight{ 800 };
};

