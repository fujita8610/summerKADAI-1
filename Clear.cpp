#include "DxLib.h"
#include "Clear.h"
#include "play.h" // 状態変更用

// タイトル画像ハンドル
static int g_ClearHandle = -1;

void InitClear()
{
    g_ClearHandle = LoadGraph("Data/scene/Title.png");
    if (g_ClearHandle == -1)
    {
        MessageBox(NULL, "Title.png が読み込めませんでした", "Error", MB_OK);
    }
}

void UpdateClear()
{
    // スペースキーでゲーム開始
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        extern void SetGameState(int state); // PlayScene側で用意
        SetGameState(g_currentScene = SCENE_TITLE); // 1はプレイシーン
    }
}

void DrawClear()
{
    if (g_ClearHandle != -1)
    {
        DrawGraph(0, 0, g_ClearHandle, TRUE); // 画面全体に描画
    }

    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));


    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));

    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));
}
