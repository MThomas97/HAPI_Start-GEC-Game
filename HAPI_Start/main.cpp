#include <HAPI_lib.h>
#include "World.h"

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

void HAPI_Main()
{
	World world;
	world.run();
}

