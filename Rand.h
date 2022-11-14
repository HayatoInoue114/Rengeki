#pragma once

enum MINUSFLAG {
	OFF,
	ON
};

/// <summary>
/// 乱数
/// </summary>
/// <param name="min">自然数の最小値</param>
/// <param name="max">自然数の最大値</param>
/// <param name="minusFlag">負の値を使うかどうか。 ON または OFF で切り替え</param>
/// <returns></returns>
int RandNum(int min,int max,MINUSFLAG minusFlag);
