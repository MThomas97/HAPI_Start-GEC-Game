#pragma once
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;
class WorldModel
{
public:
	void Play(int width, int height, std::string name);

private:
	int playerPosX = { 0 };

	int playerPosY = { 0 };

	int ChessFrame = { 0 };

	int MaxFrame = { 6 };

	int numFrames = { 5 };
};

