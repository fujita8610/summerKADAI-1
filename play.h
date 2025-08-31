#pragma once


enum GameScene {
    SCENE_TITLE,
    SCENE_PLAY,

    SCENE_BOSS,
    SCENE_GAMEOVER,
    SCENE_CLEAR
};
extern GameScene g_currentScene;
// 関数のプロトタイプ宣言
void InitPlayScene();
void LoadPlayScene();
void StartPlayScene();
void StepPlayScene();
void UpdatePlayScene();
void DrawPlayScene();
void FinPlayScene();
void SetGameState(int state);