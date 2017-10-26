#pragma once
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Graphics
{
public:
	Graphics();

	void ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour);

	void Blit(BYTE *screen, int screenWidth, BYTE *texture, int textureWidth, int textureHeight, int posX, int posY);

	void BlitNoAlpha(BYTE *screen, int screenWidth, BYTE *texture, int textureWidth, int textureHeight, int posX, int posY);
	
};

