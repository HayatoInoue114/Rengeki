#include "Easing.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Function.h"

float EasingMove(float start, float end, float easingVolume) {
    return ((start)+((end)-(start)) * (easingVolume));
}

Vec2 EasingMove(const Vec2 &start, const Vec2 &end, const float &easingVolume) {
    return ((start)+((end)-(start)) * (easingVolume));
}

int IntEasingMove(long int start, long int end, float easingVolume) {
    return ((start)+(((end)-(start)) * (easingVolume)));
}

unsigned int ColorEasingMove(unsigned int statColor, unsigned int endColor, float easingVolume) {

    unsigned int redColor = Clamp(IntEasingMove((((statColor & 0xFF000000) >> (4 * 6)) & 0xFF), (((endColor & 0xFF000000) >> (4 * 6)) & 0xFF), easingVolume), 0x00, 0xFF);
    unsigned int greenColor = Clamp(IntEasingMove((((statColor & 0x00FF0000) >> (4 * 4)) & 0xFF), (((endColor & 0x00FF0000) >> (4 * 4)) & 0xFF), easingVolume), 0x00, 0xFF);
    unsigned int blueColor = Clamp(IntEasingMove((((statColor & 0x0000FF00) >> (4 * 2)) & 0xFF), (((endColor & 0x0000FF00) >> (4 * 2)) & 0xFF), easingVolume), 0x00, 0xFF);

    unsigned int alphaColor = Clamp(IntEasingMove((statColor & 0x000000FF), (endColor & 0x000000FF), easingVolume), 0x00, 0xFF);

    return (redColor << (4 * 6)) + (greenColor << (4 * 4)) + (blueColor << (4 * 2)) + (alphaColor);

}

float easeLinear(float number) {
    return number;
}

float easeOutBack(float x) {
    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return 1 + c3 * pow((x)-1, 3) + c1 * pow((x)-1, 2);
}

float easeInBack(float x) {
    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return c3 * pow(x, 3) - c1 * pow(x, 2);
}

float easeOutCirc(float x) {
    return sqrt(1 - pow(x - 1, 2));
}

float easeInCirc(float x) {
    return 1 - sqrt(1 - pow(x, 2));
}

float easeInSine(float x) {
    return 1 - cos((x * M_PI) / 2);
}

float easeOutSine(float x) {
    return sin((x * M_PI) / 2);
}

float easeInExpo(float x) {
    return x = (x == 0) ? 0 : pow(2, 10 * x - 10);
}

float easeOutExpo(float x) {
    return x = (x == 1) ? 1 : 1 - pow(2, -10 * x);
}