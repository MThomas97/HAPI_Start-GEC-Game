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

bool Sprite::Load(const std::string &filename)
{
	if (!HAPI.LoadTexture(filename, &texturePnter, width, height))
	{
		HAPI.UserMessage("File Not Found!", "Error");
		return false;
	}
	m_textureRect = Rectangle(width, height);
	//m_frameRect = Rectangle(m_textureRect.width() / numFrames, m_textureRect.height());
	return true;
}

void Sprite::Render(BYTE* screen, const Rectangle &screenRect, int posX, int posY)
{
	Rectangle clippedRect(m_textureRect);

	clippedRect.Translate(posX, posY);

	if (!clippedRect.CompletelyOutside(screenRect))
		return;

	if (clippedRect.CompletelyInside(screenRect))
		clippedRect.ClipTo(screenRect);

	clippedRect.Translate(-posX, -posY);

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

	clippedRect.Translate(posX, posY);

	if (!clippedRect.CompletelyOutside(screenRect))
		return;

	if (clippedRect.CompletelyInside(screenRect))
		clippedRect.ClipTo(screenRect);

	clippedRect.Translate(-posX, -posY);

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


