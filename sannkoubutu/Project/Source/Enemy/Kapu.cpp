#include "DxLib.h"
#include "Kapu.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Bullet/BulletManager.h"
#include "../Sound/SoundManager.h"

#define ENEMY_KAPU_CHANGE_MOVE_TIME (150)	// 方向転換するまでの時間
#define ENEMY_KAPU_SPEED	(-20.0f)
#define ENEMY_KAPU_BREAK	(0.5f) 

#define ENEMY_KAPU_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_KAPU_ACTIVE_AREA_TOP		(-100)
#define ENEMY_KAPU_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_KAPU_ACTIVE_AREA_BOTTOM	(1000)

// 撃破時のスコア
#define ENEMY_KAPU_SCORE (1000)

// 死亡エフェクトのインターバル
#define ENEMY_KAPU_DEAD_EFFECT_INTERVAL (3)

// 死亡エフェクト位置オフセット
#define ENEMY_KAPU_DEAD_EFFECT_OFFSET (16.0f)

// バレット関連
#define ENEMY_KAPU_BULLET_INTERVAL	(60)
#define ENEMY_KAPU_BULLET_SPEED		(10.0f)
#define ENEMY_KAPU_BULLET_LIFE		(300)

// HP
#define ENEMY_KAPU_HP (10)

// 変数
EnemyKapuData g_KapuData[ENEMY_KAPU_MAX] = { 0 };

// 画像ハンドル
int g_EnemyKapuHandle = 0;

// 撃破した数
int g_EnemyKapuDestroyNum = 0;

void InitKapu()
{
	// 共通変数初期化
	g_EnemyKapuHandle = 0;
	g_EnemyKapuDestroyNum = 0;

	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		kapu->handle = 0;
		kapu->bulletTimer = 0;
		kapu->hp = 0;

		kapu->posX = 0.0f;
		kapu->posY = 0.0f;
		kapu->moveX = 0.0f;
		kapu->moveY = 0.0f;

		kapu->active = false;
		kapu->isMoveChange = false;
	}
}

void LoadKapu()
{
	g_EnemyKapuHandle = LoadGraph("Data/Enemy/Kapu.png");
}

void StepKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->active) continue;

		// 徐々に減速
		kapu->moveX += ENEMY_KAPU_BREAK;

		// 移動量が反転しそうになったら止める
		if (kapu->moveX > 0.0f)
		{
			kapu->moveX = 0.0f;
		}

		// バレットタイマーをカウントダウン
		kapu->bulletTimer--;
	}
}

void UpdateKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->active) continue;

		// 移動処理
		kapu->posX += kapu->moveX;
		kapu->posY += kapu->moveY;

		// インターバル時間になったら弾発射
		if (kapu->bulletTimer <= 0)
		{
			// 弾の発射データ設定
			FireBulletData fireData =
			{
				ENEMY_KAPU_BULLET_LIFE,
				kapu->posX,
				kapu->posY + 20.0f,
				-ENEMY_KAPU_BULLET_SPEED,
				0.0f
			};
			// 発射
			FireBullet(BULLET_CATEGORY_STRAIGHT, STRAIGHT_BULLET_TYPE_KAPU, fireData, BULLET_COLLISION_TAG_ENEMY);
			
			// タイマーリセット
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;
		}

		// 画面外にでたら死亡
		if (kapu->posX <= ENEMY_KAPU_ACTIVE_AREA_LEFT || kapu->posX >= ENEMY_KAPU_ACTIVE_AREA_RIGHT)
		{
			kapu->active = false;
		}
		else if (kapu->posY <= ENEMY_KAPU_ACTIVE_AREA_TOP || kapu->posY >= ENEMY_KAPU_ACTIVE_AREA_BOTTOM)
		{
			kapu->active = false;
		}

	}

}

void DrawKapu()
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 死んでいたら処理しない
		if (!kapu->active) continue;

		DrawGraph((int)kapu->posX, (int)kapu->posY, kapu->handle, TRUE);
	}
}

void FinKapu()
{
	DeleteGraph(g_EnemyKapuHandle);
}

EnemyKapuData* GetKapu()
{
	// 配列の先頭アドレスを返却する
	return g_KapuData;
}

void CreateKapu(float posX, float posY, const EnemyParameter* param)
{
	// ポインタを使って配列を参照する
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// 未使用のKapuを探す
		if (!kapu->active)
		{
			// 生存フラグを立てる
			kapu->active = true;

			// バレットタイマーを設定
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;

			// HP
			kapu->hp = ENEMY_KAPU_HP;

			// 方向転換フラグを折る
			kapu->isMoveChange = false;

			// 画像ハンドル設定
			kapu->handle = g_EnemyKapuHandle;

			// 座標設定
			kapu->posX = posX;
			kapu->posY = posY;

			// 移動量設定
			kapu->moveX = ENEMY_KAPU_SPEED;	// 初速
			kapu->moveY = 0.0f;

			// パラメータ設定
			kapu->param = param;

			break;
		}
	}
}

void KapuHitPlayer(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// 衝突したら死亡
	kapu->active = false;

	// 死亡エフェクト
	StartAnimationEffect(ENEMY_DEAD, kapu->posX, kapu->posY, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

	// 撃破数を加算
	g_EnemyKapuDestroyNum++;
}

void KapuHitPlayerBullet(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// ダメージ
	kapu->hp--;

	// HPが0になったら死亡
	if (kapu->hp <= 0)
	{
		kapu->active = false;

		// 死亡エフェクト
		StartAnimationEffect(ENEMY_DEAD, kapu->posX + ENEMY_KAPU_DEAD_EFFECT_OFFSET, kapu->posY + ENEMY_KAPU_DEAD_EFFECT_OFFSET, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

		// スコアを加算
		int score = GetScore() + ENEMY_KAPU_SCORE;
		SetScore(score);

		// 死亡SE再生
		PlaySE(SE_ENEMY_DEAD);

		// 撃破数を加算
		g_EnemyKapuDestroyNum++;
	}
}

// 撃破数を取得
int GetKapuDestroyNum()
{
	return g_EnemyKapuDestroyNum;
}
