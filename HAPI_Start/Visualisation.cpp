#include "Visualisation.h"
#include <iostream>
#include <HAPI_lib.h>
#include "Sprite.h"

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

void Visualisation::ClearToColour(BYTE* screen, int width, int height, HAPI_TColour colour) //function clears the screen to a specific colour that is set
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			memcpy(screen + (y*width + x) * 4, &colour,4);
		}
	}
}

bool Visualisation::CreateSprite(const std::string &name, const  std::string & filename, int numFramesX, int numFramesY)
{
	if (m_spritemap.find(name) != m_spritemap.end()) // Checks if there isnt a sprite already
		std::cerr << "Already exists" << name << std::endl;

	Sprite *newSprite = new Sprite;
	
	if (!newSprite->Load(filename, numFramesX, numFramesY))
	{
		return false;
	}
	m_spritemap[name] = newSprite;
	return true;
}

bool Visualisation::initialise(int width, int height, std::string name)
{
	if (!HAPI.Initialise(width, height, name)) //Creates a window
	{
		return false;
	}
	
	m_screenRect = Rectangle(width, height);

	m_screenPnter = HAPI.GetScreenPointer();
	return true;
}

void Visualisation::RenderSprite(const std::string &name, int posX, int posY, int curFrameX, int curFrameY)
{
	m_spritemap.at(name)->Render(this->m_screenPnter, this->m_screenRect, posX, posY, curFrameX, curFrameY);
}

void Visualisation::RenderNoAlphaSprite(const std::string &name, int posX, int posY)
{
	m_spritemap.at(name)->RenderNoAlpha(this->m_screenPnter, this->m_screenRect, posX, posY);
}

Rectangle Visualisation::GetRect(const std::string &name)
{
	return m_spritemap.at(name)->getRect();
}

int Visualisation::GetNumframesX(const std::string &name)
{
	return m_spritemap.at(name)->getNumFramesX();
}

int Visualisation::GetNumframesY(const std::string &name)
{
	return m_spritemap.at(name)->getNumFramesY();
}

Visualisation::~Visualisation()
{
	for (auto &p : m_spritemap)
		delete p.second;
}
