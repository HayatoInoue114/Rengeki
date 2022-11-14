#include "Vec2.h"
#include <math.h>

Vec2::Vec2() : x(0.0f), y(0.0f) {

}

Vec2::Vec2(float x, float y) : x(x), y(y) {

}

//------------パブリック----------

Vec2 Vec2::operator+(const Vec2& other) const {
	return { x + other.x, y + other.y };
}

Vec2 Vec2::operator-(const Vec2& other) const {
	return { x - other.x, y - other.y };
}

const Vec2 Vec2::operator+=(const Vec2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

const Vec2 Vec2::operator-=(const Vec2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 Vec2::operator*(const float& other) const {
	return { (this->x) * (other), (this->y) * (other) };
}

float Vec2::length() {
	return sqrtf(powf(x, 2) + powf(y, 2));
}

float Vec2::posX() {
	return x;
}

float Vec2::posY() {
	return y;
}

Vec2 Vec2::normarize() {

	Vec2 vector;

	vector = { x,y };

	if (length() != 0) {
		vector.x = vector.x / length();
		vector.y = vector.y / length();
	}

	return vector;

}

float Vec2::ATAN2() {
	return atan2(y, x);
}

float Vec2::COSF() {
	return cosf(ATAN2());
}

float Vec2::SINF() {
	return sinf(ATAN2());
}

float Vec2::Dot(const Vec2& other) const {
	return x * other.x + y * other.y;
}

float Vec2::Cross(const Vec2& other) const {
	return x * other.y - y * other.x;
}
