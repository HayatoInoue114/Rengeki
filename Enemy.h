#pragma once
#include "Screen.h"
#include "Vec2.h"
#include "Stage.h"
#include "Function.h"
#include "Rand.h"
#include "Easing.hpp"
#include "Particle.h"

//重力の値
const float kEnemyGravity = 1.5f;

//速度減衰の値
const float kDecay = 1.0f;

//ジャンプ最大回数
const int kEnemyMaxJump = 2;

//ノックバックの距離
const Vec2 kKnockBackLength[3] = {
	{5,10},
	{10,15},
	{50,20}
};

//最大攻撃回数
const int kEnemyMaxAttack = 3;

//星砕流・落下星の攻撃数
static constexpr int kFallingStarMax = 10;

//無敵時間の最大値
const int kEnemyInvincibleTimer = 30;

//弱攻撃の向き
enum ENEMYDIRECTION {
	ENEMYLEFT,
	ENEMYRIGHT
};

//強攻撃の向き
enum SPECIALDIRECTION {
	SPECIALLEFT,
	SPECIALRIGHT
};

class Player;

class Enemy
{
public:

	Enemy(Vec2 mPosition, Vec2 mVelocity, float mRadius);

	//更新処理
	void Update(Stage& stage, Player& player);

	//描画処理
	void Draw(Screen& screen, Player& player);
	
	//ポジションリセット
	inline void ResetPosition() { mPosition.x = 500.0f; mPosition.y = 100.0f; mHitPoint = mHitPointMax[0]; }

	//座標取得
	inline Vec2 GetEnemyPosition() { return mPosition; }

	//半径取得
	inline float GetEnemyRadius() { return mRadius; }

	////////////////////　ここから攻撃の当たり判定取得関数　////////////////////
	

	//-----弱攻撃-----//

	//攻撃の座標
	inline Vec2 GetAttackPosition(int i) { return mAttackPosition[i]; }
	//攻撃の半径
	inline float GetAttackRadius(int i) { return mAttackRadius[i]; }
	//攻撃しているか
	inline bool GetIsAttack(int i) { return mIsAttack[i]; }
	//向きの取得
	inline ENEMYDIRECTION GetEnemyDirection() { return mDirection; }


	//-----強攻撃-----//

	//攻撃の座標
	inline Vec2 GetSpecialAttackPosition() { return mSpecialAttackPosition; }
	//攻撃の半径
	inline float GetSpecialAttackRadius() { return mSpecialAttackRadius; }
	//攻撃しているか
	inline bool GetIsSpecialAttack() { return mIsSpecialAttack; }
	//向きの取得
	inline SPECIALDIRECTION GetSpecialAttackDirection() { return mSpecialAttackDirection; }

	//-----星砕流・落下星-----//
	
	//左側攻撃の座標
	inline Vec2 GetLeftFallingStarPosition(int i) { return mLeftFallingStarPosition[i]; }
	//右側攻撃の座標
	inline Vec2 GetRightFallingStarPosition(int i) { return mRightFallingStarPosition[i]; }
	//攻撃の半径
	inline float GetFallingStarRadius() { return mFallingStarRadius; }
	//攻撃しているか
	inline bool GetIsFallingStarAttack(int i) { return mIsFallingStarAttack[i]; }

	//攻撃を受けているか
	inline bool GetIsHit0() { return mIsHit[0]; }
	inline bool GetIsHit1() { return mIsHit[1]; }
	inline bool GetIsHit2() { return mIsHit[2]; }

	//無敵かどうか
	inline bool GetIsEnemyInvincible() { return mIsInvincible; }
	//無敵時間の取得
	inline int GetEnemyInvincibleTime() { return mInvincibleTime; }

private:

	

	//動き
	void Move(Player player);

	//何か攻撃しているか
	bool AnyAttack();

	//当たり判定
	void Collision(Player player);

	//体力処理
	void HitPoint(Stage& stage);

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

	//ジャンプ回数
	int mJumpCount;

	//当たったかどうかの判定
	bool mIsHit[kEnemyMaxAttack];

	//敵の向いている方向
	ENEMYDIRECTION mDirection;

	//体力
	int mHitPoint;

	//体力の最大値
	int mHitPointMax[Stage::kStageMax] = { 100, 150 };
	int mTmpHitPointMax;								//一時保存変数

	//体力を代入したか
	bool mIsHitPointAssign[Stage::kStageMax];

	//ノックバックしたかどうか
	bool mKnockBack[kEnemyMaxAttack];

	//外積の値
	float mCross;

	//////////////////// ここから無敵関係 ////////////////////

	//無敵時間
	int mInvincibleTime;
	//無敵時間か
	bool mIsInvincible;
	//無敵関数
	void Invincible();


	//////////////////// ここから攻撃関係 ////////////////////

	//攻撃関数
	void AttackPattern(Player& player);
	//攻撃を開始できるか
	bool mIsStart;
	//開始するまでのフレーム
	int mStartFrame;

	//////////////////// ここから基礎移動 ////////////////////

	//-----バックステップ-----//
	//バックステップフラグ
	bool mIsBackStep;
	//イージングの増加値
	float mBackStepEasingt;
	//移動の開始地点と終了地点
	Vec2 mBackStepStartPosition;
	Vec2 mBackStepEndPosition;
	//関数
	void BackStep();

	//-----左右瞬間移動-----//
	//左右瞬間移動フラグ
	bool mIsTeleport;
	//フレーム
	int mTeleportFrame;
	//関数
	void Teleport();

	////////////////////　ここから弱攻撃　////////////////////
	
	//攻撃回数
	int mAttackCount;
	//攻撃開始しているかどうか
	bool mIsAttackStart;
	//攻撃しているかどうかの判定
	bool mIsAttack[kEnemyMaxAttack];
	//攻撃の描画時間
	int mAttackTimer;
	//攻撃の当たり判定の座標
	Vec2 mAttackPosition[kEnemyMaxAttack];
	//攻撃の当たり判定の半径
	float mAttackRadius[kEnemyMaxAttack];
	//関数
	void Attack(Player& player);
	//パーティクル
	Particle mAttackParticle[kEnemyMaxAttack];


	////////////////////　ここから強攻撃　////////////////////
	
	//攻撃が始まったかどうか
	bool mIsSpecialAttackStart;
	//攻撃しているかどうか
	bool mIsSpecialAttack;
	//敵の向き
	SPECIALDIRECTION mSpecialAttackDirection = SPECIALLEFT;
	//攻撃時の速度
	Vec2 mSpecialAttackVelocity;
	float mSpecialAttackVelocityValue;	//加算する速度
	//攻撃時間
	int mSpecialAttackFrame;
	//攻撃の当たり判定の座標
	Vec2 mSpecialAttackPosition;
	//攻撃の当たり判定の半径
	float mSpecialAttackRadius;
	//関数
	void SpecialAttack(Player& player);



	////////////////////　ここから必殺技　////////////////////

	//-----必殺技１　星砕流・落下星-----//
	//半径
	int mFallingStarRadius;
	//フラグ
	bool mIsFallingStar;
	//イージングの増加値
	float mFallingStarEasingt;
	//移動の開始地点と終了地点
	Vec2 mFallingStarStartPosition;
	Vec2 mFallingStarEndPosition;
	//フレーム値
	int mFallingStarFrame;
	//攻撃の座標
	Vec2 mLeftFallingStarPosition[kFallingStarMax];
	Vec2 mRightFallingStarPosition[kFallingStarMax];
	//攻撃フラグ
	bool mIsFallingStarAttack[kFallingStarMax];
	//攻撃数
	int mFallingStarStartValue;
	int mFallingStarEndValue;
	//関数
	void FallingStar(Player& player);


	int RandAttack;
};


