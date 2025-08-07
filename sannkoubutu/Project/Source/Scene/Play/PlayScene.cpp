#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../BackGround/BackGround.h"
#include "../../Scene/SceneManager.h"
#include "../../Bullet/BulletManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Sound/SoundManager.h"
#include "../../Collision/Collision.h"
#include "../../Effect/AnimationEffect.h"
#include "../../UI/UIImage.h"
#include "../../UI/UIText.h"
#include "../../Score/Score.h"

// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// 背景初期化
	InitBackGround();

	// プレイヤー初期化
	InitPlayer();

	// エネミー初期化
	InitEnemy();

	// 弾を初期化
	InitBullet();

	// エフェクトを初期化
	InitAnimationEffect();

	// スコア初期化
	InitScore();
}

void LoadPlayScene()
{
	// 背景ロード
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// 背景スクロール
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// プレイヤーロード
	LoadPlayer();

	// エネミーロード
	LoadEnemy();

	// 弾ロード
	LoadBullet();

	// エフェクトロード
	LoadAnimationEffect();
}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	// 各UI生成
	CreateUIImage(UI_IMAGE_PLAY_FOOTER_FRAME, 0.0f, 775.0f);// フッター枠
	CreateUIImage(UI_IMAGE_HEART, 24.0f, 800.0f);			// 残機ハート
	CreateUIText(990.0f, 840.0f, "TARGET");					// ターゲット文字
	CreateUIImage(UI_IMAGE_TARGET_KAPU, 1140.0f, 800.0f);	// ターゲットエネミー画像
	// スコア
	CreateScoreUI(30.0f, 840.0f);
	// ハイスコア
	CreateHiScoreUI(550.0f, 840.0f);

	// BGM再生
	PlayBGM(BGM_PLAY);

}

void StepPlayScene()
{
	// 背景ステップ
	StepBackGround();

	// プレイヤーステップ
	StepPlayer();

	// エネミーステップ
	StepEnemy();

	// 弾ステップ
	StepBullet();

	// エネミー出現システムをステップ
	StepEnemySpawnSystem();

	// エフェクトをステップ
	StepAnimationEffect();

	// UIステップ
	StepUIImage();
	StepUIText();
}

void UpdatePlayScene()
{
	// 背景更新
	UpdateBackGround();

	// プレイヤー更新
	UpdatePlayer();

	// エネミー更新
	UpdateEnemy();

	// 弾更新
	UpdateBullet();

	// エフェクト更新
	UpdateAnimationEffect();

	// UI更新
	UpdateUIImage();
	UpdateUIText();
	
	// 当たり判定
	CheckCollision();

	// スコア更新
	UpdateScore();

	// Kapuを２体撃破したらクリアシーンへ
	if (GetEnemyDestroyNum(ENEMY_TYPE_KAPU) >= 2)
	{
		ChangeScene(SCENE_GAME_CLEAR);
	}
}

void DrawPlayScene()
{
	// 背景描画
	DrawBackGround();

	// 弾描画
	DrawBullet();

	// エネミー描画
	DrawEnemy();

	// プレイヤー描画
	DrawPlayer();

	// エフェクト描画
	DrawAnimationEffect();

	// UI描画
	DrawUIImage();
	DrawUIText();
}

void FinPlayScene()
{
	// 背景終了
	FinBackGround();

	// プレイヤー終了
	FinPlayer();

	// エネミー終了
	FinEnemy();

	// 弾終了
	FinBullet();

	// エフェクト終了
	FinAnimationEffect();

	// UIリセット
	ResetUIImage();
	ResetUIText();

	// BGM停止
	StopBGM(BGM_PLAY);
}
