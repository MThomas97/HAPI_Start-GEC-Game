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
	~Sprite();

	bool Load(const std::string &filename, int numFrames);

	void Render(BYTE* screen, const Rectangle &screenRect, int posX, int posY, int curFrame);

	void RenderNoAlpha(BYTE* screen, const Rectangle &screenRect, int posX, int posY);

private:
	BYTE *texturePnter{ nullptr };
	Rectangle m_textureRect;
	Rectangle m_frameRect;
	//int numFrames{ 5 };
	bool HasAlpha = true;
	int width; 
	int height;
};

