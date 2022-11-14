#pragma once
#include "Screen.h"
#include "Quad.h"
#include "Vec2.h"

//パーティクルの種類
enum PARTICLETYPE {
	//拡散(オーラ型)
	PLAYERDIFFUSION,
	//拡散(通常型)
	DIFFUSION,
	//上から下へ
	TOPTOBOTTOM,
	//下から上へ
	BOTTOMTOTOP,
	//横飛沫
	WIDESPLASH,
	//半円
	HALFCIRCLE,
	//衝撃波
	SHOCKWAVE,
	//噴水
	FOUNTAIN,
	//滞在
	STAY

};

//最大数
const int kMaxParticle = 500;

class Particle
{
public:
	Particle();
	/// <summary>
	/// パーティクルを出す
	/// </summary>
	/// <param name="mParticleType">パーティクルのタイプ</param>
	/// <param name="mParticleColor">透明度抜きのパーティクルの色</param>
	/// <param name="mParticleExtinction">消滅する距離</param>
	/// <param name="mRandMin">ランダムな大きさの最小値</param>
	/// <param name="mRandMax">ランダムな大きさの最大値</param>
	/// <param name="mMaxParticle">パーティクルの最大個数</param>
	Particle(PARTICLETYPE mParticleType, int mParticleColor, float mParticleExtinction,
		int mRandMin, int mRandMax, int mMaxParticle, bool mParticleAppear);

	void Update(Vec2 position);

	void Draw(Screen& screen);

	void Reset();

	//パーティクルフラグのセット
	void SetFlag(Vec2 position);

	//出現しているかどうかのフラグを取得
	inline bool GetParticleAppear() { return mParticleAppear; }

	//出現しているフラグに変更
	inline bool SetParticleAppear() { mParticleAppear = true; return mParticleAppear; }

	//出現フラグを戻す
	inline bool ResetParticleAppear() { mParticleAppear = false; return mParticleAppear; }

private:

	void Move(Vec2 position);

	//////////////// 使用時に入れる仮変数 /////////////

	//パーティクルの種類
	PARTICLETYPE mParticleType;

	//パーティクルの色
	int mParticleColor;

	//パーティクルの消滅する距離
	float mParticleExtinction;

	//パーティクルの大きさの乱数の最小値
	int mRandMin;

	//パーティクルの大きさの乱数の最大値
	int mRandMax;

	//パーティクルの最大数
	int mMaxParticle;

	//パーティクルのオンオフ
	bool mParticleAppear;

	///////////////////////////////////

	//座標
	Vec2 mPosition[kMaxParticle];

	//速度
	Vec2 mVelocity[kMaxParticle];

	//色
	int mColor[kMaxParticle];

	//乱数で与える透明度
	int mRandColor[kMaxParticle];

	//半径
	int mRadius[kMaxParticle];

	//フラグの管理
	bool mIsAlive[kMaxParticle];

	//出現のクールタイム
	int mCoolTime;

	//画像
	int mTextureHandle;

	//角度
	float mTheta;

	//衝撃波の移動時間
	int mShockWaveTimer;

};




