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
	float TakeDamage;			// ダメージ量
	int life;					// 残機数
	float posX;					// X座標
	float posY;					// Y座標
	int width;					// 幅
	int height;					// 高さ
	float moveX;				// X移動量
	float moveY;				// Y移動量
	float score;				// スコアS
	float medarustoko;        // メダルストックS

	float speedBuff;      // 移動速度バフ
	float shotIntervalBuff;  // 弾速バフ
	float damageBuff;     // ダメージバフ
	bool hasExtraLife;   // 残機アップ権利

	bool slotActive;   // スロットマシン使用中フラグ
	int slotTimer;    // スロットマシンタイマー
	float BBcount;  // BBカウント
	float RBcount;  // RBカウント
};

extern PlayerData g_PlayerData;


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

//スロット
void AddMedarus(int num);
void UseSlotReward();
PlayerData* GetSlotPlayer();

void SlotBB();
void SlotRB();
void SlotBELL();
void SlotCHERRY();
void SlotRBSpeed();
void SlotRBShotFast();
void SlotRBDamageUp();
void SlotRBLife();