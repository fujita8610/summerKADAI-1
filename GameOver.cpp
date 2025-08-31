#include "DxLib.h"
#include "GameOver.h"
#include "play.h" // 状態変更用

// タイトル画像ハンドル
static int g_GameOverHandle = -1;

void InitGameOver()
{
    g_GameOverHandle = LoadGraph("Data/scene/Title.png");
    if (g_GameOverHandle == -1)
    {
        MessageBox(NULL, "Title.png が読み込めませんでした", "Error", MB_OK);
    }
}

void UpdateGameOver()
{
    // スペースキーでゲーム開始
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        extern void SetGameState(int state); // PlayScene側で用意
        SetGameState(g_currentScene = SCENE_TITLE); // 1はプレイシーン
    }
}

void DrawGameOver()
{
    if (g_GameOverHandle != -1)
    {
        DrawGraph(0, 0, g_GameOverHandle, TRUE); // 画面全体に描画
    }

    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));


    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));

    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));
}

