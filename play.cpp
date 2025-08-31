#include "DxLib.h"
#include "play.h"
#include "BackGround.h"
#include "../夏休み課題１/so-su/player.h"
#include "SlotMachine.h"
#include "Enemy.h"
#include "Boss.h"
#include "Title.h"




GameScene g_currentScene = { SCENE_TITLE };

void InitPlayScene() {
    InitBackGround();
    InitPlayer();
    InitSlotReels();
    InitEnemies();
    // 他の初期化処理
}

void LoadPlayScene() {
    LoadBackGround("Data/scene/BackGround1.png", BACK_GROUND_LAYER_1);
    LoadPlayer();
    // 他のロード処理
}
void StartPlayScene() {
    StartPlayer();
    // 他のスタート処理
}
void StepPlayScene() {
    // シーンごとのステップ処理
    switch (g_currentScene) {
	case SCENE_TITLE:
        // タイトルシーンのステップ処理
        

         InitTitle();
         UpdateTitle();
         DrawTitle();


		break;


    case SCENE_PLAY:
        StepBackGround();
        StepPlayer();
        UpdateEnemies();
        UpdateSlotMachine();
        // 他の更新処理
        break;

      
   
    
	case SCENE_CLEAR:
        // クリアシーンのステップ処理
        if (CheckHitKey(KEY_INPUT_Z))
        {
            g_currentScene = SCENE_TITLE;
            // タイトルシーンに戻る処理
        }
        break;
    case SCENE_GAMEOVER:
        // ゲームオーバーシーンのステップ処理
        if (CheckHitKey(KEY_INPUT_Z))
        {
            g_currentScene = SCENE_TITLE;
            // タイトルシーンに戻る処理
		}
		break;
    }
}
void UpdatePlayScene() {
    // ここでは特に何もしない
}
void DrawPlayScene() {
  DrawBackGround();
    
  switch (g_currentScene) {
    case SCENE_TITLE:
        DrawString(540, 360
            , "Press Z to Start",
            GetColor(255, 255, 255));
        break;
    case SCENE_PLAY:
        DrawPlayer();
        DrawSlotMachine();
        DrawEnemies();
        // 他の描画処理
        break;
    case SCENE_CLEAR:
        DrawString(540, 360,
            "Game Clear! Press Z to Return to Title", GetColor(255, 255, 255));
        break;
    case SCENE_GAMEOVER:
        DrawString(540, 360,
            "Game Over! Press Z to Return to Title", GetColor(255, 255, 255));
        break;
  }

  DrawFormatString(10, 10,
      GetColor(255, 255, 255),
      "Score: %.0f", g_PlayerData.score);

  DrawFormatString(10, 40,
      GetColor(255, 255, 255),
	  "Medarus: %.0f", g_PlayerData.medarustoko);

  DrawFormatString(10, 70,
      GetColor(255, 255, 255),
	  "BB: %.0f", g_PlayerData.life);
}


void FinPlayScene() {
    // 終了処理
    // 必要に応じてリソース解放など
}




// シーンを変更する関数
void SetGameState(int state)
{
    g_currentScene == state;
}
