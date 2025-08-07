#include "DxLib.h"
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../BackGround/BackGround.h"
#include "../../Sound/SoundManager.h"
#include <math.h>

// 背景のスピード
#define BACK_GROUND_SPEED (-0.3f)

// タイトルの位置
#define TITLE_POS_X (280)
#define TITLE_POS_Y (130)

// PressZKeyの位置
#define PRESS_Z_KEY_POS_X (500)
#define PRESS_Z_KEY_POS_Y (530)

// PressZKeyの点滅スピード
#define PRESS_Z_KEY_BLINK_SPEED (0.04f)

// 画像ハンドル
int g_BGHandle = 0;
int g_TitleHandle = 0;
int g_PressZKeyHandle = 0;

// PressZKye点滅用変数
float g_PressZKeyAlpha = 0.0f;	// アルファ値
float g_PressZKeyRadian = 0.0f;	// cos関数に渡すラジアン値

void InitTitleScene()
{
	g_BGHandle = 0;
	g_TitleHandle = 0;
	g_PressZKeyHandle = 0;
	g_PressZKeyAlpha = 0.0f;
	g_PressZKeyRadian = 0.0f;

	// 背景初期化
	InitBackGround();
}

void LoadTitleScene()
{
	// 背景は背景システムを使う
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// 背景を下にスクロールさせる
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// 各画像をロード
	g_BGHandle = LoadGraph("Data/Title/TitleBG.png");
	g_TitleHandle = LoadGraph("Data/Title/TitleText.png");
	g_PressZKeyHandle = LoadGraph("Data/Title/TitlePressZKey.png");
}

void StartTitleScene()
{
	// BGM再生
	PlayBGM(BGM_TITLE);
}


void StepTitleScene()
{
	// sin波の値からPressZKeyのアルファ値（透明度）を計算する
	// sinfが-1～1の値を返却するので加工して0～1の値にしている
	g_PressZKeyAlpha = (sinf(g_PressZKeyRadian) + 1) / 2;

	// ラジアン値を点滅速度で加算
	g_PressZKeyRadian += PRESS_Z_KEY_BLINK_SPEED;

	// ラジアン値は0～2πをループさせる
	if (g_PressZKeyRadian > DX_TWO_PI_F)
	{
		g_PressZKeyRadian -= DX_TWO_PI_F;
	}

	// Zキーが押されたらプレイシーンへ
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_PLAY);
	}

	// 背景ステップ
	StepBackGround();
}

void UpdateTitleScene()
{
	// 背景更新
	UpdateBackGround();
}

void DrawTitleScene()
{
	// 背景描画
	DrawBackGround();

	// タイトル描画
	DrawGraph(TITLE_POS_X, TITLE_POS_Y, g_TitleHandle, TRUE);

	// 点滅のためにブレンドモードを設定する(DXLibの仕様が0～255で指定するので加工する)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(g_PressZKeyAlpha * 255));

	// Press Z Key 描画
	DrawGraph(PRESS_Z_KEY_POS_X, PRESS_Z_KEY_POS_Y, g_PressZKeyHandle, TRUE);

	// ブレンドモードを戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FinTitleScene()
{
	// 背景終了
	FinBackGround();

	// 各画像を削除
	DeleteGraph(g_TitleHandle);
	DeleteGraph(g_PressZKeyHandle);

	// BGM停止
	StopBGM(BGM_TITLE);
}
