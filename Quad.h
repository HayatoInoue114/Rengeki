#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Vec2.h"
#include <Novice.h>

typedef struct Quad {
	Vec2 LeftTop;
	Vec2 RightTop;
	Vec2 LeftBottom;
	Vec2 RightBottom;
};

Quad Scaling(Quad quad, float scale);
Quad XScaling(Quad quad, float scale);
Quad YScaling(Quad quad, float scale);
Quad Rotate(Quad quad, float theta);
Quad Translation(Quad quad, Vec2 position);

Quad CenterQuad(Vec2 center, float radius);

class Draw
{
public:

	static void drawQuad(Quad quad, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color);

private:

};



