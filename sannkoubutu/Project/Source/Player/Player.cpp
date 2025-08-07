#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Bullet/BulletManager.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundManager.h"

// 残機表示の文字列
#define PLAYER_LIFE_STRING ("x%02d")

// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (200.0f)
#define PLAYER_DEFAULT_POS_Y (250.0f)
#define PLAYER_MOVE_SPEED (3.0f)

// 弾関連
#define PLAYER_NORMAL_SHOT_SPEED	(32.0f)
#define PLAYER_NORMAL_SHOT_LIFE		(600)
#define PLAYER_NORMAL_SHOT_OFFSET_X	(50.0f)
#define PLAYER_NORMAL_SHOT_OFFSET_Y	(10.0f)
#define PLAYER_NORMAL_SHOT_INTERVAL (15)

// 移動可能エリア
#define PLAYER_MOVE_AREA_LEFT (0.0f)
#define PLAYER_MOVE_AREA_RIGHT (1536.0f)
#define PLAYER_MOVE_AREA_TOP (0.0f)
#define PLAYER_MOVE_AREA_BOTTOM (743.0f)

// プレイヤーの残機
#define PLAYER_DEFAULT_LIFE (2)

// リスポーンまでの待機時間
#define PLAYER_RESPAWN_WAIT (180)

// リスポーン時の無敵時間
#define PLAYER_RESPAWN_INVISIBLE_TIME (180)

// プレイヤー死亡エフェクトインターバル
#define PLAYER_DEAD_EFFECT_INTERVAL (2)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.life = 0;
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.bulletIntervalTimer = 0;
	g_PlayerData.respawnTimer = 0;
	g_PlayerData.active = false;
	g_PlayerData.invisible = false;
	g_PlayerData.lifeText = nullptr;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 残機の初期値設定
	g_PlayerData.life = PLAYER_DEFAULT_LIFE;

	// 残機のUI生成
	char text[256];
	sprintf_s(text, PLAYER_LIFE_STRING, g_PlayerData.life);
	g_PlayerData.lifeText = CreateUIText(60.0f, 795.0f, text);
}

void StepPlayer()
{
	// 死んでいたら専用処理
	if (!g_PlayerData.active)
	{
		// 待機時間が過ぎたらリスポーン
		if (g_PlayerData.respawnTimer <= 0)
		{
			bool isSuccessRespawn = RespawnPlayer();
			// リスポーンできなかったらゲームオーバー
			if (!isSuccessRespawn)
			{
				ChangeScene(SCENE_GAME_OVER);
			}
		}
		g_PlayerData.respawnTimer--;

		return;
	}

	// 移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;

	// 通常弾のインターバル時間を減らす
	if (g_PlayerData.bulletIntervalTimer > 0)
	{
		g_PlayerData.bulletIntervalTimer--;
	}

	// 上入力
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.moveY = -PLAYER_MOVE_SPEED;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	}

	// Z入力
	if (IsInputKey(KEY_Z))
	{
		// インターバル時間がすぎてから撃つ
		if (g_PlayerData.bulletIntervalTimer <= 0)
		{
			// 弾発射情報を設定
			const FireBulletData FIRE_DATA =
			{
				PLAYER_NORMAL_SHOT_LIFE,
				g_PlayerData.posX + PLAYER_NORMAL_SHOT_OFFSET_X,
				g_PlayerData.posY + PLAYER_NORMAL_SHOT_OFFSET_Y,
				PLAYER_NORMAL_SHOT_SPEED,
				0.0f,
			};
			FireBullet(BULLET_CATEGORY_STRAIGHT, STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, FIRE_DATA, BULLET_COLLISION_TAG_PLAYER);

			// 発射音再生
			PlaySE(SE_PLAYRE_SHOT);

			// インターバル設定
			g_PlayerData.bulletIntervalTimer = PLAYER_NORMAL_SHOT_INTERVAL;
		}
	}

	// 無敵中の処理
	if (g_PlayerData.invisible)
	{
		g_PlayerData.invisibleTimer--;
	}
}

void UpdatePlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

	// 画面外に出ないように移動制限
	if (g_PlayerData.posX < PLAYER_MOVE_AREA_LEFT) g_PlayerData.posX = PLAYER_MOVE_AREA_LEFT;
	if (g_PlayerData.posX > PLAYER_MOVE_AREA_RIGHT) g_PlayerData.posX = PLAYER_MOVE_AREA_RIGHT;
	if (g_PlayerData.posY < PLAYER_MOVE_AREA_TOP) g_PlayerData.posY = PLAYER_MOVE_AREA_TOP;
	if (g_PlayerData.posY > PLAYER_MOVE_AREA_BOTTOM) g_PlayerData.posY = PLAYER_MOVE_AREA_BOTTOM;

	// 無敵解除チェック
	if (g_PlayerData.invisible && g_PlayerData.invisibleTimer <= 0)
	{
		g_PlayerData.invisible = false;
	}
}

void DrawPlayer()
{
	// 死んでいたら処理しない
	if (!g_PlayerData.active) return;

	// 無敵の時は点滅する
	if (g_PlayerData.invisible)
	{
		// 3フレームに1度だけ描画して点滅させる
		if (g_PlayerData.invisibleTimer % 3 == 0)
		{
			DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
		}
	}
	else
	{
		// 通常描画
		DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
	}
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

// リスポーン処理(リスポーンできなかったらfalseを返す)
bool RespawnPlayer()
{
	// 残機チェック
	if (g_PlayerData.life > 0)
	{
		// アクティブ
		g_PlayerData.active = true;

		// 無敵状態
		g_PlayerData.invisible = true;
		g_PlayerData.invisibleTimer = PLAYER_RESPAWN_INVISIBLE_TIME;

		// 初期位置に配置
		g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
		g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;

		// 残機を減らす
		g_PlayerData.life--;

		// 残機UI更新
		char text[256];
		sprintf_s(text, PLAYER_LIFE_STRING, g_PlayerData.life);
		SetUIText(g_PlayerData.lifeText, text);

		// リスポーン成功
		return true;
	}

	// リスポーン不可
	return false;
}

void PlayerDead()
{
	// 死亡
	g_PlayerData.active = false;

	// リスポーン待機開始
	g_PlayerData.respawnTimer = PLAYER_RESPAWN_WAIT;

	// 死亡エフェクト
	StartAnimationEffect(PLAYER_DEAD, g_PlayerData.posX, g_PlayerData.posY, PLAYER_DEAD_EFFECT_INTERVAL);

	// 死亡SE
	PlaySE(SE_PLAYER_DEAD);
}

// 敵と衝突した
void PlayerHitEnemy()
{
	// 衝突したら死亡
	PlayerDead();
}

// 敵の弾と衝突した
void PlayerHitEnemyBullet()
{
	// 衝突したら死亡
	PlayerDead();
}
