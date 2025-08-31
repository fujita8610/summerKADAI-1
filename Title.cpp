#include "DxLib.h"
#include "Title.h"
#include "play.h" // 状態変更用

// タイトル画像ハンドル
static int g_TitleHandle = -1;

void InitTitle()
{
    g_TitleHandle = LoadGraph("Data/scene/Title.png");
    if (g_TitleHandle == -1)
    {
        MessageBox(NULL, "Title.png が読み込めませんでした", "Error", MB_OK);
    }
}

void UpdateTitle()
{
    // スペースキーでゲーム開始
    if (CheckHitKey(KEY_INPUT_SPACE))
    {
        extern void SetGameState(int state); // PlayScene側で用意
        SetGameState(g_currentScene = SCENE_PLAY);
    }
}

void DrawTitle()
{
    if (g_TitleHandle != -1)
    {
        DrawGraph(0, 0, g_TitleHandle, TRUE); // 画面全体に描画
    }

    DrawString(200, 400, "Press SPACE to START",
        GetColor(255, 255, 255));
}
