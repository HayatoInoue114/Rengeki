#include "Quad.h"

Quad Scaling(Quad quad, float scale) {
	return { {quad.LeftTop.x * scale,		quad.LeftTop.y * scale},
			 {quad.RightTop.x * scale,		quad.RightTop.y * scale},
			 {quad.LeftBottom.x * scale,	quad.LeftBottom.y * scale},
			 {quad.RightBottom.x * scale,	quad.RightBottom.y * scale}
	};
}
Quad XScaling(Quad quad, float scale) {
	return { {quad.LeftTop.x * scale,		quad.LeftTop.y},
			 {quad.RightTop.x * scale,		quad.RightTop.y},
			 {quad.LeftBottom.x * scale,	quad.LeftBottom.y},
			 {quad.RightBottom.x * scale,	quad.RightBottom.y}
	};
}
Quad YScaling(Quad quad, float scale) {
	return { {quad.LeftTop.x,		quad.LeftTop.y * scale},
			 {quad.RightTop.x,		quad.RightTop.y * scale},
			 {quad.LeftBottom.x,	quad.LeftBottom.y * scale},
			 {quad.RightBottom.x,	quad.RightBottom.y * scale}
	};
}
Quad Rotate(Quad quad, float theta) {
	float c = cosf(theta);
	float s = sinf(theta);
	return { {quad.LeftTop.x * c - quad.LeftTop.y * s ,			quad.LeftTop.y * c + quad.LeftTop.x * s },
			 {quad.RightTop.x * c - quad.RightTop.y * s ,		quad.RightTop.y * c + quad.RightTop.x * s },
			 {quad.LeftBottom.x * c - quad.LeftBottom.y * s ,	quad.LeftBottom.y * c + quad.LeftBottom.x * s },
			 {quad.RightBottom.x * c - quad.RightBottom.y * s , quad.RightBottom.y * c + quad.RightBottom.x * s }
	};
}
Quad Translation(Quad quad, Vec2 position) {
	return { {quad.LeftTop.x + position.x,        quad.LeftTop.y + position.y},
			 {quad.RightTop.x + position.x,       quad.RightTop.y + position.y},
			 {quad.LeftBottom.x + position.x,     quad.LeftBottom.y + position.y},
			 {quad.RightBottom.x + position.x,    quad.RightBottom.y + position.y}
	};
}

Quad CenterQuad(Vec2 center, float radius) {

	Quad tmp{
		{ center.x - radius, center.y - radius},
		{ center.x + radius, center.y - radius},
		{ center.x - radius, center.y + radius},
		{ center.x + radius, center.y + radius}
	};

	return tmp;

}

void Draw::drawQuad(Quad quad, int srcX, int srcY, int srcW, int srcH, int textureHandle, unsigned int color) {

	Novice::DrawQuad(quad.LeftTop.x, quad.LeftTop.y, quad.RightTop.x, quad.RightTop.y, quad.LeftBottom.x, quad.LeftBottom.y, quad.RightBottom.x, quad.RightBottom.y, srcX, srcY, srcW, srcH, textureHandle, color);
}