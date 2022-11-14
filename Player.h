#pragma once
#include "Screen.h"
#include "Vec2.h"
#include "Stage.h"
#include "Particle.h"

//重力の値
const float kGravity = 1.5f;

//ジャンプ最大回数
const int kMaxJump = 2;

//最大攻撃回数
const int kMaxAttack = 3;

//攻撃力
const int kAttackValue[kMaxAttack] = { 2, 5, 20 };

//攻撃の持続時間
const int kAttackPersistence = 30;

//無敵時間の最大値
const int kInvincibleTimer = 30;

//プレイヤーの向き
enum DIRECTION {
	LEFT,
	RIGHT
};

class Enemy;

class Player
{
public:
	/// <summary>
	/// プレイヤーの初期化
	/// </summary>
	/// <param name="mPosition">初期座標</param>
	/// <param name="mVelocity">速度</param>
	/// <param name="mRadius">半径</param>
	Player();
	/// <summary>
	/// プレイヤーの初期化
	/// </summary>
	/// <param name="mPosition">初期座標</param>
	/// <param name="mVelocity">速度</param>
	/// <param name="mRadius">半径</param>
	Player(Vec2 mPosition, Vec2 mVelocity, float mRadius);

	//更新処理
	void Update(Stage& stage, Enemy &enemy);

	//描画処理
	void Draw(Screen& screen);

	//向きの取得
	inline DIRECTION GetPlayerDirection() { return mDirection; }

	//半径取得
	inline float GetPlayerRadius() { return mRadius; }

	//攻撃の当たり判定の取得
	inline float GetAttackPositionX0() { return mAttackPosition[0].x; }
	inline float GetAttackPositionX1() { return mAttackPosition[1].x; }
	inline float GetAttackPositionX2() { return mAttackPosition[2].x; }
	inline float GetAttackPositionY0() { return mAttackPosition[0].y; }
	inline float GetAttackPositionY1() { return mAttackPosition[1].y; }
	inline float GetAttackPositionY2() { return mAttackPosition[2].y; }

	inline Vec2 GetAttackPositionX(int i) { return mAttackPosition[i]; }

	inline float GetAttackRadius0() { return mAttackRadius[0]; }
	inline float GetAttackRadius1() { return mAttackRadius[1]; }
	inline float GetAttackRadius2() { return mAttackRadius[2]; }

	inline bool GetIsAttack0() { return mIsAttack[0]; }
	inline bool GetIsAttack1() { return mIsAttack[1]; }
	inline bool GetIsAttack2() { return mIsAttack[2]; }

	inline bool GetIsHit0() { return mIsHit[0]; }
	inline bool GetIsHit1() { return mIsHit[1]; }
	inline bool GetIsHit2() { return mIsHit[2]; }

	inline int GetAttackTimer() { return mAttackTimer; }

	//プレイヤーの座標取得（外積に使用する）
	inline Vec2 GetPlayerPosition() { return mPosition; }

	//無敵かどうか
	inline bool GetIsPlayerInvincible() { return mIsInvincible; }
	//無敵時間の取得
	inline int GetPlayerInvincibleTime() { return mInvincibleTime; }

private:

	//動き
	void Move();

	//当たり判定
	void Collision(Stage& stage, Enemy& enemy);
	bool CircleCollision(Vec2 AttackPosition, float AttackRadius);


	

	//座標
	Vec2 mPosition;

	//速度
	Vec2 mVelocity;

	//ノックバック時の速度
	Vec2 mKnockBackVelocity;

	//半径
	float mRadius;

	//色
	int mColor;

	//地面についているか
	bool mIsGround;

	//当たったかどうかの判定
	bool mIsHit[kMaxAttack];

	//ノックバックしたかどうか
	bool mKnockBack[kMaxAttack];

	//プレイヤーの向いている方向
	DIRECTION mDirection;

	//----------動き関係----------//
	//---攻撃---//
	//攻撃回数
	int mAttackCount;
	//攻撃しているかどうかの判定
	bool mIsAttack[kMaxAttack];
	//攻撃の描画時間
	int mAttackTimer;
	//攻撃の当たり判定の座標
	Vec2 mAttackPosition[kMaxAttack];
	//攻撃の当たり判定の半径
	float mAttackRadius[kMaxAttack];
	//攻撃関数
	void Attack();
	//パーティクル
	Particle mAttackParticle[kMaxAttack];

	//サウンド
	int mAttackSE[kMaxAttack];

	//---ジャンプ---//
	//ジャンプ回数
	int mJumpCount;
	//ジャンプ関数
	void Jump();
	
	//---ローリング---//
	//ローリングしているかどうか
	bool mIsRolling;
	//ローリング中のフレーム
	int mRollingFrame;
	//ローリング関数
	void Rolling();


	//----------無敵関係----------//
	//無敵時間
	int mInvincibleTime;
	//無敵時間か
	bool mIsInvincible;
	//無敵関数
	void Invincible();


	//----------描画関係----------//
	//描画するフラグ
	bool mIsLoad;
	int player;

	//描画

};



