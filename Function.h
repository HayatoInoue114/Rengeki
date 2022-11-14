#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include<cstdlib>
#include<ctime>

/*　比較　*/
void Comparison(int& num, int num1);

/*　線形補間　*/
float Lerp(float easing, int end);

/*　数値を収める関数　*/
float Clamp(float t, float min, float max); 

/*　度数を入れるとラジアンに変換する関数　*/
float Degree(float degree);
/*　ラジアンを入れると度数に変換する関数　*/
float Radian(float radian);

/*　ランダム　*/
int RAND(int min, int max);
void SRAND();