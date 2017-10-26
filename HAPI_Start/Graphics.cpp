#include "Graphics.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;


Graphics::Graphics()
{
}

void Graphics::ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour) //function clears the screen to a specific colour that is set
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			memcpy(screen + (y*width + x) * 4, &colour, 4);
		}
	}
}

void Graphics::Blit(BYTE *screen, int screenWidth, BYTE *texture, int textureWidth, int textureHeight, int posX, int posY) //Makes sprite visual onscreen with RBG values and alpha transparency
{
	int endOfLineScreenIncrement = (screenWidth - textureWidth) * 4;

	BYTE *screenPnter = screen + (posX + posY*screenWidth) * 4;

	BYTE *texturePnter = texture;

	for (int y = 0; y < textureHeight; y++)
	{
		for (int x = 0; x < textureWidth; x++)
		{

			BYTE blue = texturePnter[0];
			BYTE green = texturePnter[1];
			BYTE red = texturePnter[2];
			BYTE alpha = texturePnter[3];

			float mod = alpha / 255.0f;
			screenPnter[0] = screenPnter[0] + ((alpha*(blue - screenPnter[0])) >> 8);
			screenPnter[1] = screenPnter[1] + ((alpha*(green - screenPnter[1])) >> 8);
			screenPnter[2] = screenPnter[2] + ((alpha*(red - screenPnter[2])) >> 8);

			texturePnter += 4;
			screenPnter += 4;

		}

		screenPnter += endOfLineScreenIncrement;
	}
}


void Graphics::BlitNoAlpha(BYTE *screen, int screenWidth, BYTE *texture, int textureWidth, int textureHeight, int posX, int posY) //Makes sprite visual onscreen with RBG values for sprites that don't need alpha value
{
	BYTE *screenPnter = screen + (posX + posY*screenWidth) * 4;

	BYTE *texturePnter = texture;

	for (int y = 0; y < textureHeight; y++)
	{
		memcpy(screenPnter, texturePnter, textureWidth * 4);

		//Move texture pointer to next line
		texturePnter += textureWidth * 4;

		//Move screen pointer to next line
		screenPnter += screenWidth * 4;
	}
}