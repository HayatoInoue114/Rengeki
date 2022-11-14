#include "Rand.h"
#include <stdlib.h>

int RandNum(int min, int max,MINUSFLAG minusFlag) {

	if ((max + 1 - min) == 0) {
		return 1;
	}

	int number = (rand() % (max + 1 - min)) + min;

	if (minusFlag == ON) {

		int plusOrMinus = rand() % 2;

		if (plusOrMinus == 0) {
			return number;
		}
		else {
			return -number;
		}

	}

	return number;

}