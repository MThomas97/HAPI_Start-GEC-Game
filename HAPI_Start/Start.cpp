#include "Start.h"
#include "Textures.h"
#include "Graphics.h"
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

Start::Start()
{
}

void Start::Play(int width, int height, std::string name)
{
	if (!HAPI.Initialise(width, height, name))
		return;

	const HAPI_TKeyboardData & keyData = HAPI.GetKeyboardData();

	BYTE *BYTEtexture{ nullptr };

	BYTE *BYTEbackground{ nullptr };

	Textures textures;
	
	textures.LoadTexture("Data\\alphaThing.tga", &BYTEtexture, textures.TextureWidth, textures.TextureHeight);
	
	textures.LoadTexture("Data\\starBackground.png", &BYTEbackground, textures.BackgroundWidth, textures.BackgroundHeight);
	
	Graphics graphics;

	while (HAPI.Update()) //Game loop
	{	//calls functions from classes
		graphics.ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));

		graphics.BlitNoAlpha(HAPI.GetScreenPointer(), width, BYTEbackground, textures.BackgroundWidth, textures.BackgroundHeight, 0, 0);

		graphics.Blit(HAPI.GetScreenPointer(), width, BYTEtexture, textures.TextureWidth, textures.TextureHeight, textures.texturePosX, textures.texturePosY);

		if (textures.texturePosY > 0) { //Moves sprite with WASD keys

			if (keyData.scanCode['W'])
				textures.texturePosY -= 1;
		}

		if (textures.texturePosY < height - textures.TextureHeight)
		{
			if (keyData.scanCode['S'])
				textures.texturePosY += 1;
		}

		if (textures.texturePosX > 0)
		{
			if (keyData.scanCode['A'])
				textures.texturePosX -= 1;
		}

		if (textures.texturePosX < width - textures.TextureWidth)
		{
			if (keyData.scanCode['D'])
				textures.texturePosX += 1;
		}


	}
	delete[] BYTEtexture;
	delete[] BYTEbackground;

	
}




