// Boss.h
#pragma once
#include "DxLib.h"

struct BossData {
    bool active;       // 出現中かどうか
    float posX, posY;  // 座標
    int hp, maxHp;     // 体力
    int handle;        // 画像
    int phase;         // 行動フェーズ
    int timer;         // フェーズ進行用タイマー
};

void InitBoss();
void SpawnBoss();
void UpdateBoss();
void DrawBoss();
void KillBoss();
bool IsBossActive();
