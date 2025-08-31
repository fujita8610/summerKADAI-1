// Boss.cpp
#include "Boss.h"
#include "../夏休み課題１/so-su/player.h"
#include "Enemy.h"
#include "play.h"
#include "sound.h"
#include <math.h>
BossData g_Boss;
EnemyData g_EnemyData;

void InitBoss() 
{
    g_Boss.active = false;
}

void SpawnBoss()
{
	// 既存の敵を全て消す
    g_Boss.active = true;
    g_Boss.posX = 1400;   // 右から登場
    g_Boss.posY = 200;
    g_Boss.hp = 300;      // 体力多め
    g_Boss.maxHp = 300;
    g_Boss.handle = LoadGraph("Data/SE/scene/boss.png");
    g_Boss.phase = 0;
    g_Boss.timer = 0;

	PlaySE(SE_BOSS_STAND);

    ClearAllEnemies(); // 既存の敵を全て消す
}

void UpdateBoss() {
    if (!g_Boss.active) return;

    g_Boss.timer++;

    // 移動パターン（例：ゆっくり左右に動く）
    if (g_Boss.phase == 0) {
        g_Boss.posX -= 2;   // 左へ登場
        if (g_Boss.posX < 1000) {
            g_Boss.phase = 1;
            g_Boss.timer = 0;
        }
    }
    else if (g_Boss.phase == 1) 
    {
        g_Boss.posX 
            += sinf(g_Boss.timer * 0.05f)
            * 3;
        g_Boss.posY 
            += cosf(g_Boss.timer * 0.02f)
            * 2;

        // 弾を撃つ
        if (g_Boss.timer % 60 == 0)
        {
            // ここで弾を発射（円形にばらまく等）
            // FireBossBullet(g_Boss.posX, g_Boss.posY);
        }
    }

    // HPチェック
    if (g_Boss.hp <= 0)
    {
        KillBoss();
    }
}

void DrawBoss() {
    if (!g_Boss.active) return;

    DrawGraph((int)g_Boss.posX,
        (int)g_Boss.posY, g_Boss.handle, TRUE);

    // HPバー表示
    int barWidth = 400;
    int hpWidth = (int)(barWidth
        * ((float)g_Boss.hp / g_Boss.maxHp));

    DrawBox(500, 20, 500 + barWidth, 50, 
        GetColor(100, 100, 100), TRUE);
    DrawBox(500, 20, 500 + hpWidth, 50, 
        GetColor(255, 50, 50), TRUE);
}

void KillBoss()
{
    g_Boss.active = false;
	PlaySE(SE_BOSS_DEAD);

    float bosstimer = 0;


    // 倒したら報酬（スロットBBクリアとか）
    AddMedarus(10); // 大量のコインドロップ

	g_currentScene = SCENE_CLEAR; // クリアシーンへ
}

bool IsBossActive() {
    return g_Boss.active;
}
