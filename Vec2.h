#pragma once

//struct Vec2
//{
// float x;
// float y;
//}

class Vec2 {

	//アクセス範囲 : 外からいじれない
private:


	//アクセス範囲 : 外からいじれる、見れる
public:

	float x;
	float y;

	//デフォルトコンストラクタ
	Vec2();

	//引数ありコンストラクタ(多重定義、オーバーロード)
	Vec2(float x, float y);

	Vec2 operator+(const Vec2& other) const;//Vec2 + Vec2
	Vec2 operator-(const Vec2& other) const;//Vec2 - Vec2

	const Vec2 operator+=(const Vec2& other);//Vec2 += Vec2
	const Vec2 operator-=(const Vec2& other);//Vec2 -= Vec2

	Vec2 operator*(const float& other) const;

	float length();
	float posX();
	float posY();

	Vec2 normarize();

	/// <summary>
	/// 座標を入力して角度を出す
	/// </summary>
	/// <returns>求めたラジアン値</returns>
	float ATAN2();

	/// <summary>
	/// 単位円上の x 値
	/// </summary>
	/// <returns>ベクトルのラジアンを算出し、 x 値を返す</returns>
	float COSF();

	/// <summary>
	/// 単位円上の y 値
	/// </summary>
	/// <returns>ベクトルのラジアンを算出し、 y 値を返す</returns>
	float SINF();

	/// <summary>
	/// 引数のベクトルとの内積
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>float型</returns>
	float Dot(const Vec2& other) const;

	/// <summary>
	/// 引数のベクトルとの外積
	/// </summary>
	/// <param name="other"> Vec2</param>
	/// <returns>float型</returns>
	float Cross(const Vec2& other) const;

};