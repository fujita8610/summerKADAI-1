#include "DxLib.h"
#include "../夏休み課題１/so-su/player.h"
#include "bulletstring.h"
#include "SlotMachine.h"
#include "Enemy.h"
#include "Boss.h"
#include "GameSetting.h"
#include "sound.h"
#include "../夏休み課題１/so-su/FPS/FPS.h"
#include "Score.h"  
#include "BackGround.h"
#include "Clear.h"
#include "Title.h"
#include "GameOver.h"
#include "play.h"
#include "UIImage.h"

// TODO: 敵やボスのヘッダもインクルード

// プロトタイプ宣言
void GameInit();
void GameUpdate();
void GameDraw();
void GameEnd();

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    // DXライブラリ初期化
    ChangeWindowMode(TRUE); // ウィンドウモード
    SetGraphMode(1280, 720, 32);
    if (DxLib_Init() == -1) return -1;

    // ウィンドウサイズ設定
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // 透過色の設定
    SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);
    SetDrawScreen(DX_SCREEN_BACK);

    // ゲーム初期化
    GameInit();

    // メインループ
    while (ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        GameUpdate(); // 更新処理
        GameDraw();   // 描画処理
        ScreenFlip(); // 裏画面を表に反映
    }

    // 終了処理
    GameEnd();
    DxLib_End();
    return 0;
}

// ゲーム初期化
void GameInit()
{
    InitFPS();
    InitBackGround();
    InitPlayer();
    InitEnemies();
    InitBoss();

    // 弾初期化
    InitStraightBullet();
    LoadStraightBullet();

    // スロット初期化
    InitSlotReels();
    InitScore();

    LoadBGM();

    InitClear();
	InitTitle();
	InitGameOver();

}

// 更新処理
void GameUpdate()
{
	UpdateFPS();
    UpdateBackGround();
    UpdatePlayer();
    UpdateEnemies();
    UpdateBoss();

    // 弾の更新
    UpdateStraightBullet();

    // スロット更新
    UpdateSlotMachine();
    UpdateScore();

    CheckBulletCollision();

	
    UpdateClear();
	UpdateTitle();
	UpdateGameOver();

}

// 描画処理
void GameDraw()
{
    DrawFPS();
  
	// 背景描画
    DrawBackGround();
    // プレイヤー描画
	 DrawPlayer();

	 // 敵描画
     DrawEnemies();

	 DrawBoss();
    // 弾の描画
    DrawStraightBullet();

    // スロットの描画
    DrawSlotMachine();

    DrawClear();
	DrawTitle();
    DrawGameOver();

  
}

// 終了処理
void GameEnd()
{
    FinBackGround();
    FinPlayer();
    FinStraightBullet();
	FinBGM();
}
