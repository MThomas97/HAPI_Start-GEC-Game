/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file
	
	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there are two batch files for creating a redistributable Demo folder
*/

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;
void ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour); 



void SetPixel(BYTE* screen, int width, int height, int x, int y, HAPI_TColour col)
{
	memcpy(screen + (y*width + x) * 4, &col, 4); //Sets a pixel on the screen a one byte
	
}

void ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour) //function clears the screen to a specific colour that is set
{
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++)
		{
			memcpy(screen + (y*width + x) * 4, &colour, 4);
		}
	}
}


void Blit(BYTE *screen, int screenWidth, BYTE *texture, int textureWidth, int textureHeight, int posX, int posY)
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

void BlitNoAlpha(BYTE *screen, int screenWidth, BYTE * texture, int textureWidth, int textureHeight, int posX, int posY)
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

bool LoadTexture(const std::string &filename, BYTE** data, int &width, int &height)
{
	int textureWidth, textureHeight;
	if (!HAPI.LoadTexture(filename, data, textureWidth, textureHeight))
	{
		HAPI.UserMessage("File Not Found!", "Error");
		return false;
	}
}

// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down

void HAPI_Main()
{
	int width{ 1280 };
	int height{ 720 };

	const HAPI_TKeyboardData & keyData = HAPI.GetKeyboardData();

	int TextureWidth{ 64 };
	int TextureHeight{ 64 };

	int BackgroundWidth{ 200 };
	int BackgroundHeight{ 200 };

	int texturePosX{ 200 };
	int texturePosY{ 200 };

	BYTE *texture{ nullptr };

	BYTE *background{ nullptr };

	if (!HAPI.Initialise(width, height, "Killin Zone"))
		return;
	
	//HAPI.SetShowFPS(true);
	
	LoadTexture("Data\\alphaThing.tga", &texture, TextureWidth, TextureHeight);

	HAPI.LoadTexture("Data\\background.tga", &background, BackgroundWidth, BackgroundHeight);

	//Blit(HAPI.GetScreenPointer(), width, background, BackgroundWidth, BackgroundHeight, 0, 0);

	

	while (HAPI.Update()) //Game loop 
	{

		ClearToColour(HAPI.GetScreenPointer(), width, height, HAPI_TColour(0, 0, 0));
				
		BlitNoAlpha(HAPI.GetScreenPointer(), width, background, BackgroundWidth, BackgroundHeight, 0, 0);

		Blit(HAPI.GetScreenPointer(), width, texture, TextureWidth, TextureHeight, texturePosX, texturePosY);

		

		if (texturePosY > 0) {

			if (keyData.scanCode['W'])
				texturePosY -= 1;
		}

		if (texturePosY < height - TextureHeight)
		{
			if (keyData.scanCode['S'])
				texturePosY += 1;
		}

		if (texturePosX > 0)
		{
			if (keyData.scanCode['A'])
				texturePosX -= 1;
		}

		if (texturePosX < width - TextureWidth)
		{
			if (keyData.scanCode['D'])
				texturePosX += 1;
		}

		
	}
	delete[] texture;
	delete[] background;
}

