#pragma once
#include <algorithm>
#include <unordered_map>
#include <HAPI_lib.h>

#if defined(DEBUG) | defined(_DEBUG)
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__, __LINE__)
#endif

// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

class Rectangle
{
public:
	Rectangle() = default;

	Rectangle(int l, int r, int t, int b);
	Rectangle(int w, int h) : left(0), right(w), top(0), bottom(h) {}

	void Translate(int dx, int dy);

	void ClipTo(const Rectangle &other);

	bool ClipToReset(const Rectangle & other);

	bool CompletelyOutside(const Rectangle &other);

	bool CompletelyInside(const Rectangle &other);

	bool CheckCollision(const Rectangle &source, const Rectangle &dest);

	int left, right, top, bottom;
	int width() const { return right - left; }
	int height() const { return bottom - top; }
	
};

