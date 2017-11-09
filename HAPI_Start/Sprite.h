#pragma once
#include <HAPI_lib.h>
#include <algorithm>
#include "Rectangle.h"

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
	Sprite();

	~Sprite();

	bool Load(const std::string &filename, int width, int height);

	void Render(BYTE* screen, const Rectangle &screenRect, int posX, int posY);

	void RenderNoAlpha(BYTE* screen, const Rectangle &screenRect, int posX, int posY);

private:
	BYTE *texturePnter{ nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;
	int numFrames{ 1 };
	bool HasAlpha = true;
};

