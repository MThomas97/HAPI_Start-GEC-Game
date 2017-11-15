#pragma once
#include "Visualisation.h"
#include"Vector2.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Entity
{
public:
	Entity();

	virtual void Update() = 0;
	
protected:

	int health{ 100 };
	float MoveSpeed{ 3 };
	int curFrameX{ 0 };
	int curFrameY{ 0 };
	//float PrevTime{ 0 };
	//float ElapsedTime = HAPI.GetTime() - PrevTime;
};

