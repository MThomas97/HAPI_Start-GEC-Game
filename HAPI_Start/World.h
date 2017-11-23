#pragma once
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;
class Visualisation;

class Entity;

class World
{
public:

	~World();

	void run(int width, int height, std::string name);

	void Update(int width, int height, std::string name);

	void LoadLevel();

private:
	
	std::vector<Entity*> m_entity;

	Visualisation *m_vis{ nullptr };

	int SecondScrollPosX = { 0 };
	int SecondScrollPosY = { -800 };
	int ScrollPosX = { 0 };
	int ScrollPosY = { 0 };
	/*int numFramesX = { 5 };
	int numFramesY = { 3 };
	int curFrameX = { 0 };
	int curFrameY = { 0 };*/
	float MoveSpeed{ 5 };
	int prevTime = 0;
	//int playerPrevTime = 0;
};

