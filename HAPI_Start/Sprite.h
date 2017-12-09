#pragma once
#include <HAPI_lib.h>
#include <algorithm>
#include "Rectangle.h"
#include "Vector2.h"

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Rectangle;

class Sprite
{
public:
	~Sprite();

	bool Load(const std::string &filename, int numFramesX, int numFramesY);

	void Render(BYTE* screen, const Rectangle &screenRect, int posX, int posY, int curFrameX, int curFrameY);

	void RenderNoAlpha(BYTE* screen, const Rectangle &screenRect, int posX, int posY);

	Rectangle getRect() { return m_frameRect; }

	int getNumFramesX() { return tempNumFramesX; }

	int getNumFramesY() { return tempNumFramesY; }

private:
	BYTE *texturePnter{ nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;
	bool HasAlpha = true;
	int width, height;
	int tempNumFramesX, tempNumFramesY;
	
};

