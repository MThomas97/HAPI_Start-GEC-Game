#include "Sprite.h"
#include <vector>
#include <HAPI_lib.h>
#include "Rectangle.h"

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Rectangle;

bool Sprite::Load(const std::string &filename, int numFramesX, int numFramesY)
{
	if (!HAPI.LoadTexture(filename, &texturePnter, width, height))
	{
		HAPI.UserMessage("File Not Found!", "Error");
		return false;
	}

	m_textureRect = Rectangle(width, height); //gets the width and height of the texture
	m_frameRect = Rectangle(m_textureRect.width() / numFramesX, m_textureRect.height() / numFramesY);
	return true;
}

void Sprite::Render(BYTE* screen, const Rectangle &screenRect, int posX, int posY, int curFrameX, int curFrameY)
{
	Rectangle clippedRect(m_frameRect);

	clippedRect.Translate(posX, posY); //Translates clippedRect into screen space by adding posX and posY

	if (clippedRect.CompletelyOutside(screenRect) == true) //Checks if completely outside the screen and exits the code if true
		return;

	//if (clippedRect.CompletelyInside(screenRect) == false) //Checks if completely contained if so then don't clipTo
	//{
	//	clippedRect.ClipTo(screenRect); //clip rectangle is clipped against screen rectangle ////////////////////FIX THIS!!! <----
	//}

	clippedRect.ClipTo(screenRect);

	clippedRect.Translate(-posX, -posY); //Translates clippedRect back into screen space by subtracting

	clippedRect.Translate(m_frameRect.width() * curFrameX, m_frameRect.height() * curFrameY); //Translates to the curFrame e.g 2 would be the second frame thats rendered

	if (posX < 0)
	posX = 0;

	if (posY < 0)
	posY = 0;
	
	int endOfLineScreenIncrement = (screenRect.width() - clippedRect.width()) * 4;

	int endOfLineTextureIncrement = (m_textureRect.width() - clippedRect.width()) * 4;

	BYTE *tempScreen = screen + (posX + posY * screenRect.width()) * 4;

	BYTE *tempText = texturePnter + (clippedRect.left + clippedRect.top * m_textureRect.width()) *4;

	for (int y = 0; y < clippedRect.height(); y++)
	{

		for (int x = 0; x < clippedRect.width(); x++)
		{
			if (HasAlpha)
			{//sets texturePnter to blue, green, red, alpha
				BYTE blue = tempText[0];
				BYTE green = tempText[1];
				BYTE red = tempText[2];
				BYTE alpha = tempText[3];

				if (alpha == 255) //if alpha is 255 just straight copy it
				{
					memcpy(tempScreen, tempText,  4);
				}
				else  //if there is no alpha do nothing if there is do alpha blending
				{
					tempScreen[0] = tempScreen[0] + ((alpha*(blue - tempScreen[0])) >> 8);
					tempScreen[1] = tempScreen[1] + ((alpha*(green - tempScreen[1])) >> 8);
					tempScreen[2] = tempScreen[2] + ((alpha*(red - tempScreen[2])) >> 8);
				}
			}
			tempText += 4;
			tempScreen += 4;
		}
		tempScreen += endOfLineScreenIncrement;
		tempText += endOfLineTextureIncrement;
	}
}


void Sprite::RenderNoAlpha(BYTE* screen, const Rectangle &screenRect, int posX, int posY) //Makes sprite visual onscreen with RBG values for sprites that don't need alpha value
{
	Rectangle clippedRect(m_textureRect);

	/*if (clippedRect.ClipToReset(screenRect))
	{
		posX = 0;
		posY = 0;

	}*/
	

	clippedRect.Translate(posX, posY); //Translates clippedRect into screen space by adding posX and posY

	if (clippedRect.CompletelyOutside(screenRect) == true)
		return;

	//if (clippedRect.CompletelyInside(screenRect) == false) //Checks if completely contained if so then don't clipTo
	//{
	//	clippedRect.ClipTo(screenRect); //clip rectangle is clipped against screen rectangle ////////////////////FIX THIS!!! <----
	//}
	
	clippedRect.ClipTo(screenRect); //clip rectangle is clipped against screen rectangle

	clippedRect.Translate(-posX, -posY); //Translates clippedRect back into screen space by subtracting

	if (posX < 0)
		posX = 0;

	if (posY < 0)
		posY = 0;

	int endOfLineScreenIncrement = (screenRect.width() - clippedRect.width()) * 4;

	int endOfLineTextureIncrement = (m_textureRect.width() - clippedRect.width()) * 4;

	BYTE *tempScreen = screen + (posX + posY * screenRect.width()) * 4;

	BYTE *tempText = texturePnter + (clippedRect.left + clippedRect.top * m_textureRect.width()) * 4;

	for (int y = 0; y < clippedRect.height(); y++)
	{

		for (int x = 0; x < clippedRect.width(); x++)
		{	
			memcpy(tempScreen, tempText, 4);
					
			tempText += 4;
			tempScreen += 4;
		}
		tempScreen += endOfLineScreenIncrement;
		tempText += endOfLineTextureIncrement;
	}
}

Sprite::~Sprite()
{
	delete[] texturePnter;
}


