#pragma once

// プレイヤーサイズ
#define PLAYER_WIDTH	(64.0f)
#define PLAYER_HEIGHT	(64.0f)
#define PLAYER_RADIUS	(32.0f)

// プレイヤーデータ
struct PlayerData
{
	bool active;				// 生存フラグ
	bool invisible;				// 無敵フラグ
	int handle;					// 画像ハンドル
	int bulletIntervalTimer;	// 弾の発射間隔タイマー
	int respawnTimer;			// リスポーン待機タイマー
	int invisibleTimer;			// 無敵時間タイマー
	int life;					// 残機数
	float posX;					// X座標
	float posY;					// Y座標
	float moveX;				// X移動量
	float moveY;				// Y移動量
	
};


// 関数のプロトタイプ宣言
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();

// リスポーン処理(リスポーンできなかったらfalseを返す)
bool RespawnPlayer();

// 当たり判定
void PlayerHitEnemy();
void PlayerHitEnemyBullet();
