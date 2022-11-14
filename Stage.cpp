#include "Stage.h"
#include "Player.h"
#include "Enemy.h"



void Stage::HitStop(Player& player, Enemy& enemy) {

	//攻撃を受けた時ヒットストップフラグをtrueにする
	if (mIsHitStop == false && ((player.GetIsPlayerInvincible() == true && player.GetPlayerInvincibleTime() == 29) ||
								(enemy.GetIsEnemyInvincible() == true && enemy.GetEnemyInvincibleTime() == 29))){
		mIsHitStop = true;

	}

	if (mIsHitStop == true){

		//フレームを加算する
		mHitStopFrame++;

		if (mHitStopFrame >= 6){
			mIsHitStop = false;
		}

	}

	if (mIsHitStop == false){

		mHitStopFrame = 0;

	}

}

void Stage::Draw(int Flame) {
	Novice::DrawSprite(0, 0, Flame, 1, 1, 0.0f, WHITE);
}
