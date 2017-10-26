#pragma once
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Textures
{
public:
	Textures();

	bool LoadTexture(const std::string &filename, BYTE** data, int &width, int &height);

	int TextureWidth{ 64 };
	int TextureHeight{ 64 };

	int BackgroundWidth{ 254 };
	int BackgroundHeight{ 256 };

	int texturePosX{ 200 };
	int texturePosY{ 200 };

};

