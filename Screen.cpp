#include "Screen.h"

Screen::Screen(){
	ScreenShake = { 0.0f, 0.0f };
	Zoom = { 1.0f, 1.0f };
};

void Screen::Shake(int minX, int maxX, int minY, int maxY, bool is) {
	if (is == true) {
		ScreenShake.x = RAND(minX, maxX);
		ScreenShake.y = RAND(minY, maxY);
	}
	else {
		ScreenShake = { 0.0f, 0.0f };
	}
}

Vec2 Screen::SetScreen(Vec2 Position) {
	Vec2 tmpPosition;
	tmpPosition.x = Position.x + ScreenShake.x;
	tmpPosition.y = Position.y + ScreenShake.y;
	return tmpPosition;
}



void Screen::DrawBox(Vec2 Position, float w, float h, float angle, unsigned int color, FillMode fillMode) {
	float x = Position.x * Zoom.x + ScreenShake.x;
	float y = Position.y * Zoom.y - ScreenShake.y;
	Novice::DrawBox(static_cast<int>(x), static_cast<int>(y), w, h, angle, color, fillMode);
}


void Screen::DrawEllipse(Vec2 Position, float radius, float angle, unsigned int color, FillMode fillMode) {
	float x = Position.x * Zoom.x + ScreenShake.x;
	float y = Position.y * Zoom.y - ScreenShake.y;
	Novice::DrawEllipse(static_cast<int>(x), static_cast<int>(y),  radius * Zoom.x,  radius * Zoom.y,  angle,  color, fillMode);
}

void Screen::DrawQuad(Quad quad, float srcX, float srcY, float srcW, float srcH, float textureHandle, unsigned int color) {
	float x1 = quad.LeftTop.x * Zoom.x + ScreenShake.x;
	float y1 = quad.LeftTop.y * Zoom.y - ScreenShake.y;
	float x2 = quad.RightTop.x * Zoom.x + ScreenShake.x;
	float y2 = quad.RightTop.y * Zoom.y - ScreenShake.y;
	float x3 = quad.LeftBottom.x * Zoom.x + ScreenShake.x;
	float y3 = quad.LeftBottom.y * Zoom.y - ScreenShake.y;
	float x4 = quad.RightBottom.x * Zoom.x + ScreenShake.x;
	float y4 = quad.RightBottom.y * Zoom.y - ScreenShake.y;
	Novice::DrawQuad(static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2), static_cast<int>(x3), static_cast<int>(y3), static_cast<int>(x4), static_cast<int>(y4), srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawAnime(Quad quad, int& srcX, int srcW, int srcH, int sheets, int frame, int& framehensuu, int textureHandle, unsigned int color) {
	float x1 = quad.LeftTop.x * Zoom.x + ScreenShake.x;
	float y1 = quad.LeftTop.y * Zoom.y - ScreenShake.y;
	float x2 = quad.RightTop.x * Zoom.x + ScreenShake.x;
	float y2 = quad.RightTop.y * Zoom.y - ScreenShake.y;
	float x3 = quad.LeftBottom.x * Zoom.x + ScreenShake.x;
	float y3 = quad.LeftBottom.y * Zoom.y - ScreenShake.y;
	float x4 = quad.RightBottom.x * Zoom.x + ScreenShake.x;
	float y4 = quad.RightBottom.y * Zoom.y - ScreenShake.y;
	if (framehensuu % frame == 0) {
		srcX += srcW;
	}
	if (srcX >= srcW * sheets){
		srcX = 0;
	}
	Novice::DrawQuad(x1, y1, x2, y2, x3, y3, x4, y4, srcX, 0, srcW, srcH, textureHandle, color);
}
