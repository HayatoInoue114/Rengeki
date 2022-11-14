#include <Novice.h>
#include <time.h>
#include "Player.h"
#include "Stage.h"
#include "Key.h"
#include "Enemy.h"
#include "Particle.h"
#include "Rand.h"
#include <time.h>

const char kWindowTitle[] = "1203_Rengeki";

clock_t oldTime;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//リソース読み込み
	int Flame = Novice::LoadTexture("./Resources/Stage/Flame.png");

	//乱数生成
	unsigned int kCurrentTime = time(nullptr);

	srand(kCurrentTime);

	Screen screen;

	Player player({ 100.0f,100.0f }, { 7.0f,7.0f }, 30.0f);
	Enemy enemy({ 500.0f,100.0f }, { 5.0f,5.0f }, 30.0f);
	Stage stage;

	Particle stageParticle(BOTTOMTOTOP, 0xFFFFFF00, 0, 1, 3, 500, true);

	Particle enemyParticle(PLAYERDIFFUSION, 0xFF00FF00, 
		(enemy.GetEnemyRadius() / 2), enemy.GetEnemyRadius() + 12, enemy.GetEnemyRadius() + 13, 100, true);

	Particle enemyParticle2(STAY, 0xFF00FF00,
		(enemy.GetEnemyRadius() / 2), enemy.GetEnemyRadius() - 25, enemy.GetEnemyRadius() - 15, 100, true);

	Particle playerParticle(PLAYERDIFFUSION, 0x00FFFF00,
		(player.GetPlayerRadius() / 2), player.GetPlayerRadius() + 12, player.GetPlayerRadius() + 13, 100, true);

	Particle playerParticle2(STAY, 0x00FFFF00, 
		(player.GetPlayerRadius() / 2), player.GetPlayerRadius() - 25, player.GetPlayerRadius() - 15, 100, true);

	Vec2 stageParticlePosition = { 0,800 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//キー入力の更新
		Key::Update();

		while (!((oldTime + 16) - clock() <= 0));


		///
		/// ↓更新処理ここから
		///

		if (stage.mIsHitStop == false) {

			if (Key::IsTrigger(DIK_R)) {
				enemy.ResetPosition();
			}

			player.Update(stage, enemy);
			enemy.Update(stage, player);
			stageParticle.SetFlag(stageParticlePosition);
			stageParticle.Update(stageParticlePosition);
			enemyParticle.SetFlag(enemy.GetEnemyPosition());
			enemyParticle.Update(enemy.GetEnemyPosition());
			enemyParticle2.SetFlag(enemy.GetEnemyPosition());
			enemyParticle2.Update(enemy.GetEnemyPosition());
			playerParticle.SetFlag(player.GetPlayerPosition());
			playerParticle.Update(player.GetPlayerPosition());
			playerParticle2.SetFlag(player.GetPlayerPosition());
			playerParticle2.Update(player.GetPlayerPosition());

		}

		stage.HitStop(player, enemy);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::DrawBox(0, 0, kWindowWidth, kWindowHeight, 0.0, BLACK, kFillModeSolid);
		stage.Draw(Flame);
		stageParticle.Draw(screen);
		enemyParticle.Draw(screen);
		enemyParticle2.Draw(screen);
		playerParticle.Draw(screen);
		playerParticle2.Draw(screen);
		player.Draw(screen);
		enemy.Draw(screen, player);

		Novice::ScreenPrintf(70, 40, "Move : Arrow Left or Arrow Right Key");
		Novice::ScreenPrintf(70, 60, "Jump : Arrow Up Key");
		Novice::ScreenPrintf(70, 80, "Attack : C Key");
		Novice::ScreenPrintf(70, 100, "Rolling : X Key");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		oldTime = clock();

		// ESCキーが押されたらループを抜ける
		if (Key::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
