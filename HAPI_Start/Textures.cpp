#include "Textures.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

Textures::Textures()
{
}

bool Textures::LoadTexture(const std::string &filename, BYTE** data, int & width, int & height)
{
	int textureWidth, textureHeight;
	if (!HAPI.LoadTexture(filename, data, textureWidth, textureHeight))
	{
		HAPI.UserMessage("File Not Found!", "Error");
		return false;
	}
}
