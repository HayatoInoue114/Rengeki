#include "Player.h"
#include "Vec2.h"
#include <Novice.h>
#include "Key.h"
#include <math.h>
#include "Enemy.h"
#include "Quad.h"

Player::Player()
{
}

Player::Player(Vec2 mPosition, Vec2 mVelocity, float mRadius)
	: mPosition(mPosition),mVelocity(mVelocity),mRadius(mRadius)
{

	for (int i = 0; i < 3; i++) {
		mAttackParticle[i] = Particle(DIFFUSION, 0x00FFFF00, 300, 3, 5, 100, false);
	}

	mColor = 0xFFFFFFFF;
	mAttackCount = kMaxAttack;
	mJumpCount = 0;
	mIsGround = false;
	mIsRolling = false;
	mRollingFrame = 0;
	mDirection = RIGHT;
	mAttackTimer = 0;
	mIsAttack[0] = false;
	mIsAttack[1] = false;
	mIsAttack[2] = false;
	mAttackPosition[0].x = mPosition.x + 32;
	mAttackPosition[0].x = mPosition.x + 64;
	mAttackPosition[0].x = mPosition.x + 96;
	mAttackPosition[0].y = mPosition.y;
	mAttackPosition[1].y = mPosition.y;
	mAttackPosition[2].y = mPosition.y;
	mAttackRadius[0] = 16;
	mAttackRadius[1] = 16;
	mAttackRadius[2] = 16;
	mIsHit[0] = false;
	mIsHit[1] = false;
	mIsHit[2] = false;
	mKnockBack[0] = false;
	mKnockBack[1] = false;
	mKnockBack[2] = false;
	mInvincibleTime = 0;
	mIsInvincible = false;
	mIsLoad = false;
	mAttackSE[0] = Novice::LoadAudio("./Resources/SE/punch1.wav");
	mAttackSE[1] = Novice::LoadAudio("./Resources/SE/punch2.wav");
	mAttackSE[2] = Novice::LoadAudio("./Resources/SE/punch3.wav");

}



void Player::Update(Stage &stage, Enemy &enemy) {

	//攻撃パーティクルの更新
	for (int i = 0; i < kEnemyMaxAttack; i++) {

		if (mIsAttack[i] == true) {
			mAttackParticle[i].Update(mAttackPosition[i]);
		}

	}

	Move();

	Collision(stage, enemy);

}



//----------ここから動き関係----------//
void Player::Move() {

	//重力を加算
	mVelocity.y += kGravity;

	//地面にいる場合重力加算を無効
	if (mIsGround == true) {
		mVelocity.y = 0;
		mKnockBackVelocity.y = 0;
	}

	//攻撃フラグが立っている場合、一定時間でフラグを戻す
	if (mAttackTimer > 0) {
		mAttackTimer -= 1;
	}

	//プレイヤーの場合の操作

	//攻撃していない場合のみ行動できる
	if (mIsAttack[0] == false) {

		//右移動
		if (Key::IsPress(DIK_RIGHT) && mIsRolling == false) {
			mPosition.x += mVelocity.x;
			mDirection = RIGHT;
		}

		//左移動
		if (Key::IsPress(DIK_LEFT) && mIsRolling == false) {
			mPosition.x -= mVelocity.x;
			mDirection = LEFT;
		}

		//ジャンプ
		Jump();

		//ローリング
		Rolling();

	}

	//攻撃
	Attack();

	//速度を加算
	mPosition.y += mVelocity.y;

	//速度減衰
	if (mKnockBackVelocity.x > 0) {
		mKnockBackVelocity.x -= kDecay;

		if (mKnockBackVelocity.x <= 0) {
			mKnockBackVelocity.x = 0;
		}

	}
	else if (mKnockBackVelocity.x < 0) {
		mKnockBackVelocity.x += kDecay;

		if (mKnockBackVelocity.x >= 0) {
			mKnockBackVelocity.x = 0;
		}

	}

	//ノックバック時の速度を加算
	mPosition.x += mKnockBackVelocity.x;
	mPosition.y += mKnockBackVelocity.y;
}
void Player::Attack() {

	//攻撃座標を設定
	if (mDirection == LEFT) {
		mAttackPosition[0].x = mPosition.x - 32;
		mAttackPosition[1].x = mPosition.x - 64;
		mAttackPosition[2].x = mPosition.x - 96;
	}

	if (mDirection == RIGHT) {
		mAttackPosition[0].x = mPosition.x + 32;
		mAttackPosition[1].x = mPosition.x + 64;
		mAttackPosition[2].x = mPosition.x + 96;
	}

	mAttackPosition[0].y = mPosition.y;
	mAttackPosition[1].y = mPosition.y;
	mAttackPosition[2].y = mPosition.y;

	if (Key::IsTrigger(DIK_C) && mIsRolling == false) {

		if (mIsGround == true) {

			//一撃目
			if (mAttackCount == 3 && mIsAttack[0] == false) {
				mAttackTimer = kAttackPersistence;
				mIsAttack[0] = true;
				mAttackParticle[0].SetFlag(mAttackPosition[0]);
				Novice::PlayAudio(mAttackSE[0], 0, 0.5f);
				mAttackCount -= 1;
			}

			//二撃目
			else if (mAttackCount == 2 && mIsAttack[1] == false) {
				mAttackTimer = kAttackPersistence;
				mIsAttack[1] = true;
				mAttackParticle[1].SetFlag(mAttackPosition[1]);
				Novice::PlayAudio(mAttackSE[1], 0, 0.5f);
				mAttackCount -= 1;
			}

			//三撃目
			else if (mAttackCount == 1 && mIsAttack[2] == false) {
				mAttackTimer = kAttackPersistence;
				mIsAttack[2] = true;
				mAttackParticle[2].SetFlag(mAttackPosition[2]);
				Novice::PlayAudio(mAttackSE[2], 0, 0.5f);
				mAttackCount -= 1;
			}

		}

	}

	//タイマーが0になったらフラグを戻す
	if (mAttackTimer == 0) {

		for (int i = 0; i < kMaxAttack; i++) {
			mIsAttack[i] = false;
			mAttackParticle[i].Reset();
		}

		mAttackCount = kMaxAttack;
	}

}
void Player::Jump() {

	//ジャンプ
	if (Key::IsTrigger(DIK_UP) && mIsRolling == false) {

		//ジャンプ回数が残っている場合ジャンプできる
		if (mJumpCount > 0) {
			mVelocity.y = 0;
			mVelocity.y -= 20.0f;
			mJumpCount -= 1;
		}

	}
}
void Player::Rolling() {

	//ローリングフラグを立てる
	if (Key::IsTrigger(DIK_X) && mIsGround == true) {
		mIsRolling = true;
	}

	//一定時間ローリングする
	if (mIsRolling == true) {
		mRollingFrame++;
		mColor = 0xFFFFFF77;

		if (mDirection == RIGHT) {
			mPosition.x += 18.0f;
		}
		if (mDirection == LEFT) {
			mPosition.x -= 18.0f;
		}

		if (mRollingFrame >= 15) {
			mRollingFrame = 0;
			mIsRolling = false;
		}
	}
}



//----------ここから当たり判定----------//
void Player::Collision(Stage& stage, Enemy& enemy) {

	//左判定
	if (mPosition.x - mRadius < Stage::kStageLeft) {
		mPosition.x = Stage::kStageLeft + mRadius;
	}

	//右判定
	if (mPosition.x + mRadius > Stage::kStageRight) {
		mPosition.x = Stage::kStageRight - mRadius;
	}

	//下判定
	if (mPosition.y + mRadius >= Stage::kStageBottom) {
		mPosition.y = Stage::kStageBottom - mRadius;
		mIsGround = true;
		mJumpCount = kMaxJump;
	}
	else {
		mIsGround = false;
	}

	//ローリングしてない時に攻撃を受ける
	if (mIsRolling == false && mIsInvincible == false){

		if (stage.GetRound() == Round1){

			//-----弱攻撃当たり判定-----//
			for (int i = 0; i < kEnemyMaxAttack; i++) {

				//攻撃を受けた場合
				if (CircleCollision(enemy.GetAttackPosition(i), enemy.GetAttackRadius(i)) == true && enemy.GetIsAttack(i) == true) {
					mColor = 0xFFFF00FF;
					mIsHit[i] = true;

					if (mIsInvincible == false) {
						mInvincibleTime = kInvincibleTimer;
						mIsInvincible = true;
					}

					//敵の向きによってノックバックする方向を変える
					if (enemy.GetEnemyDirection() == RIGHT && mKnockBack[i] == false) {
						mKnockBackVelocity.x = kKnockBackLength[i].x;
						mKnockBackVelocity.y = -kKnockBackLength[i].y;
						mPosition.y -= kKnockBackLength[i].y;
						mKnockBack[i] = true;
					}

					if (enemy.GetEnemyDirection() == LEFT && mKnockBack[i] == false) {
						mKnockBackVelocity.x = -kKnockBackLength[i].x;
						mKnockBackVelocity.y = -kKnockBackLength[i].y;
						mPosition.y -= kKnockBackLength[i].y;
						mKnockBack[i] = true;
					}

				}
				else {
					mIsHit[i] = false;
					mKnockBack[i] = false;
				}

				//何も攻撃を受けていない時は色を戻す
				if (mIsHit[0] == false && mIsHit[1] == false && mIsHit[2] == false) {
					mColor = 0xFFFFFFFF;
				}
			}

			//-----強攻撃当たり判定-----
			//攻撃を受けた場合
			if (CircleCollision(enemy.GetSpecialAttackPosition(), enemy.GetSpecialAttackRadius()) == true && enemy.GetIsSpecialAttack() == true) {
				mColor = 0xFFFF00FF;
				mIsHit[2] = true;

				if (mIsInvincible == false) {
					mInvincibleTime = kInvincibleTimer;
					mIsInvincible = true;
				}

				//敵の向きによってノックバックする方向を変える
				if (enemy.GetSpecialAttackDirection() == SPECIALRIGHT && mKnockBack[2] == false) {
					mKnockBackVelocity.x = kKnockBackLength[2].x;
					mKnockBackVelocity.y = -kKnockBackLength[2].y;
					mPosition.y -= kKnockBackLength[2].y;
					mKnockBack[2] = true;
				}

				if (enemy.GetSpecialAttackDirection() == SPECIALLEFT && mKnockBack[2] == false) {
					mKnockBackVelocity.x = -kKnockBackLength[2].x;
					mKnockBackVelocity.y = -kKnockBackLength[2].y;
					mPosition.y -= kKnockBackLength[2].y;
					mKnockBack[2] = true;
				}

			}
			else {
				mIsHit[2] = false;
				mKnockBack[2] = false;
			}

			//-----星砕流・落下星当たり判定-----//
			for (int i = 0; i < kFallingStarMax; i++) {

				//左側攻撃を受けた場合
				if (CircleCollision(enemy.GetLeftFallingStarPosition(i), enemy.GetFallingStarRadius()) == true && enemy.GetIsFallingStarAttack(i) == true) {
					mColor = 0xFFFF00FF;
					mIsHit[2] = true;

					if (mIsInvincible == false) {
						mInvincibleTime = kInvincibleTimer;
						mIsInvincible = true;
					}

					if (mKnockBack[2] == false) {
						mKnockBackVelocity.x = -kKnockBackLength[2].x;
						mKnockBackVelocity.y = -kKnockBackLength[2].y;
						mPosition.y -= kKnockBackLength[2].y;
						mKnockBack[2] = true;
					}

				}

				//右側攻撃を受けた場合
				if (CircleCollision(enemy.GetRightFallingStarPosition(i), enemy.GetFallingStarRadius()) == true && enemy.GetIsFallingStarAttack(i) == true) {
					mColor = 0xFFFF00FF;
					mIsHit[2] = true;

					if (mIsInvincible == false) {
						mInvincibleTime = kInvincibleTimer;
						mIsInvincible = true;
					}

					if (mKnockBack[2] == false) {
						mKnockBackVelocity.x = kKnockBackLength[2].x;
						mKnockBackVelocity.y = -kKnockBackLength[2].y;
						mPosition.y -= kKnockBackLength[2].y;
						mKnockBack[2] = true;
					}

				}

				else {
					mIsHit[2] = false;
					mKnockBack[2] = false;
				}

				//何も攻撃を受けていない時は色を戻す
				if (mIsHit[2] == false) {
					mColor = 0xFFFFFFFF;
				}
			}
		}

		if (stage.GetRound() == Round2) {

		}

	}

	//無敵
	if (mIsInvincible == true) {

		Invincible();

	}

	

}
void Player::Invincible() {

	//無敵時間が0より大きいとき（Hit時に時間の最大値を代入する）
	if (mInvincibleTime > 0) {

		//1フレーム後
		if (mInvincibleTime <= 29) {
			mColor = 0xFFFFFF55;
		}

		mInvincibleTime -= 1;
		mInvincibleTime = Clamp(mInvincibleTime, 0, kInvincibleTimer);

		//時間が0になったらフラグをfalseにする
		if (mInvincibleTime == 0) {
			mIsInvincible = false;
		}

	}
}
bool Player::CircleCollision(Vec2 AttackPosition, float AttackRadius) {

	int x = mPosition.x - AttackPosition.x;
	int y = mPosition.y - AttackPosition.y;

	if (sqrtf(x * x + y * y) <= (mRadius + AttackRadius)) {
		return true;
	}
	return false;

}



//----------ここから描画関係----------//

void Player::Draw(Screen& screen) {

	//リソースの読み込み
	if (mIsLoad == false) {
		player = Novice::LoadTexture("./Resources/Player/Player.png");
		mIsLoad = true;
	}

	//プレイヤー描画
	screen.DrawQuad(CenterQuad(mPosition, mRadius), 0, 0, 79, 128, player, 0xFFFFFFFF);

	//攻撃範囲描画
	for (int i = 0; i < kMaxAttack; i++) {

		if (mIsAttack[i] == true) {
			mAttackParticle[i].Draw(screen);
			screen.DrawEllipse(mAttackPosition[i], mAttackRadius[i], 0.0f, 0xFF0000FF, kFillModeSolid);
		}
	}

}
