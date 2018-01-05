#pragma once
#include <HAPI_lib.h>
#include "World.h"


#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Restart
{
public:
	Restart();

	void RestartGame();

	~Restart();
};

