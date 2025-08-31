#include "DxLib.h"
#include "so-su/player.h"
#include"SlotMachine.h"
#include "Enemy.h"
#include "Boss.h"
#include "play.h"
#include "sound.h"
#include "bulletstring.h"


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
#define PLAYER_SHOT_DAMAGE (1.0f)
#define MAX_SHOTS (30)

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
	g_PlayerData.life = PLAYER_DEFAULT_LIFE;
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.bulletIntervalTimer = 0;
	g_PlayerData.respawnTimer = 0;
	g_PlayerData.active = false;
	g_PlayerData.invisible = false;
	g_PlayerData.TakeDamage = 1.0f;
	g_PlayerData.width = PLAYER_WIDTH;
	g_PlayerData.height = PLAYER_HEIGHT;

	g_PlayerData.score = 0;
	g_PlayerData.medarustoko = 0;

	g_PlayerData.speedBuff = 1.0f;
	g_PlayerData.shotIntervalBuff  = 1.0f;
	g_PlayerData.damageBuff = 1.0f;
	g_PlayerData.hasExtraLife = false;
	g_PlayerData.slotActive = false;

	g_PlayerData.slotTimer = 0;
	g_PlayerData.BBcount = 0;
	g_PlayerData.RBcount = 0;

	
}


void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("");
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 残機の初期値設定
	g_PlayerData.life = PLAYER_DEFAULT_LIFE;


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
				g_currentScene = SCENE_GAMEOVER;
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

	// 無敵中の処理
	// 無敵状態時の弾の発射制御
	if (g_PlayerData.invisible) {
		g_PlayerData.bulletIntervalTimer = 0;  // 無敵中は弾を発射できない
	}
	else {
		if (g_PlayerData.bulletIntervalTimer > 0) {
			g_PlayerData.bulletIntervalTimer--;
		}
	}


}

void UpdatePlayer()
{

	
		if (!g_PlayerData.active) return;

		float speed = PLAYER_MOVE_SPEED * g_PlayerData.speedBuff;

		if (CheckHitKey(KEY_INPUT_W)) g_PlayerData.moveY = -speed;
		if (CheckHitKey(KEY_INPUT_S)) g_PlayerData.moveY = speed;
		if (CheckHitKey(KEY_INPUT_A)) g_PlayerData.moveX = -speed;
		if (CheckHitKey(KEY_INPUT_D)) g_PlayerData.moveX = speed;

		// ショット発射
	// UpdatePlayer() の発射部分
		int interval = (int)(PLAYER_NORMAL_SHOT_INTERVAL - g_PlayerData.shotIntervalBuff);
		if (interval < 1) interval = 1;

		if (CheckHitKey(KEY_INPUT_SPACE) && g_PlayerData.bulletIntervalTimer <= 0)
		{
			FireBulletData fbd{};
			fbd.posX = g_PlayerData.posX + PLAYER_NORMAL_SHOT_OFFSET_X;
			fbd.posY = g_PlayerData.posY + PLAYER_NORMAL_SHOT_OFFSET_Y;
			fbd.moveX = PLAYER_NORMAL_SHOT_SPEED;
			fbd.moveY = 0.0f;
			fbd.life = PLAYER_NORMAL_SHOT_LIFE;
			// もし与ダメを弾に持たせるなら fbd.power = PLAYER_SHOT_DAMAGE * g_PlayerData.damageBuff;

			FireStraightBullet(STRAIGHT_BULLET_TYPE_PLAYER_NORMAL,
				fbd, BULLET_COLLISION_TAG_PLAYER);

			PlaySE(SE_PLAYRE_SHOT);       // ここでSEもOK
			g_PlayerData.bulletIntervalTimer = interval;
		}

		// 入力後に位置を反映
		g_PlayerData.posX += g_PlayerData.moveX;
		g_PlayerData.posY += g_PlayerData.moveY;

		// 画面外に出ないようにクランプ
		// ...（今あるクランプでOK）

		if (g_PlayerData.bulletIntervalTimer> 0)
			g_PlayerData.bulletIntervalTimer--;
	

	// 画面外に出ないように移動制限
	if (g_PlayerData.posX < PLAYER_MOVE_AREA_LEFT) g_PlayerData.posX = PLAYER_MOVE_AREA_LEFT;
	if (g_PlayerData.posX > PLAYER_MOVE_AREA_RIGHT) g_PlayerData.posX = PLAYER_MOVE_AREA_RIGHT;
	if (g_PlayerData.posY < PLAYER_MOVE_AREA_TOP) g_PlayerData.posY = PLAYER_MOVE_AREA_TOP;
	if (g_PlayerData.posY > PLAYER_MOVE_AREA_BOTTOM) g_PlayerData.posY = PLAYER_MOVE_AREA_BOTTOM;

	// 無敵解除チェック
	if (g_PlayerData.invisible && g_PlayerData.invisibleTimer <= 0)
	{
		g_PlayerData.invisible = false;
		g_PlayerData.invisibleTimer = 0;  // 無敵タイマーをリセット
	}

	

	//更新
	UpdateSlotMachine();
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
	g_PlayerData.respawnTimer = PLAYER_RESPAWN_WAIT;

	// 強化効果をリセット
	g_PlayerData.speedBuff = 1.0f;
	g_PlayerData.shotIntervalBuff = 0;
	g_PlayerData.damageBuff = 1.0f;
	
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



void AddMedarus(int num) {
	g_PlayerData.medarustoko += num;
	//スロット回転
	if (g_PlayerData.medarustoko >= 4) {
		g_PlayerData.medarustoko -= 3;
		StartSlotMachine();
	}
	


}


enum Bonus
{
	BB,
	RB,
	BELL,
	CHERRY,

	RB_SPEED,
	RB_SHOT_FAST,
	RB_DAMAGE_UP,
	RB_LIFE
};

void SlotBB()
{
	g_PlayerData.score += 5000;
	g_PlayerData.medarustoko += 28;
	g_PlayerData.BBcount += 1;

	PlaySE(SE_SLOT_BB);

	//エフェクトとボス戦移行
	SpawnBoss();
}

void SlotRB()
{
	g_PlayerData.score += 1000;
	g_PlayerData.medarustoko += 8;
	g_PlayerData.RBcount += 1;
	PlaySE(SE_SLOT_RB);
	

	//報酬の抽選
	int reward = GetRand(4);
	if(reward == 0) SlotRBSpeed();
	else if (reward == 1) SlotRBShotFast();
	else if (reward == 2) SlotRBDamageUp();
	else if (reward == 3) SlotRBLife();
}

void SlotBELL()
{
	g_PlayerData.score += 200;
	g_PlayerData.medarustoko += 2;

}

void SlotCHERRY()
{
	g_PlayerData.score += 100;
	g_PlayerData.medarustoko += 1;
	PlaySE(SE_SLOT_CHANCE);
}

void SlotRBSpeed()
{
	g_PlayerData.speedBuff = 1.5f;  // 移動速度を1.5倍
}

void SlotRBShotFast()
{
	//弾の発射速度アップ
	g_PlayerData.shotIntervalBuff += 0.5f;
}

void SlotRBDamageUp()
{
	g_PlayerData.damageBuff = 1.5f; // 与えるダメージを1.5倍
}

void SlotRBLife()
{
	float prevLife = g_PlayerData.life;

	//残機アップ
	g_PlayerData.hasExtraLife = true;

	if(g_PlayerData.hasExtraLife 
		&& g_PlayerData.life < 9)
	{
		g_PlayerData.life++;
		g_PlayerData.hasExtraLife = false;
	}
}

