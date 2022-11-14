#include "Function.h"

/*　比較　*/
void Comparison(int& num, int num1) {
	if (num < num1) {
		num = num1;
	}
};

/*　線形補間　*/
float Lerp(float easing, int end) {
	return (1.0f - easing) * 0 + easing * end;
}

/*　数値を収める関数　*/
float Clamp(float num, float min, float max) {
	if (num >= max) {
		return max;
	}
	if (num <= min) {
		return min;
	}
	return num;
};

/*　度数を入れるとラジアンに変換する関数　*/
float Degree(float degree) {
	return degree * (M_PI / 180);
}
/*　ラジアンを入れると度数に変換する関数　*/
float Radian(float radian) {
	return radian * (180 / M_PI);
}

/*　ランダム　*/
int RAND(int min, int max) {
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
float RAND(float min, float max) {
	return min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
void SRAND() {
	srand((unsigned)time(NULL));
}