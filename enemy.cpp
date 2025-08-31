// Enemy.cpp
#include "Enemy.h"
#include "../夏休み課題１/so-su/player.h"
#include "DxLib.h"
#include "Boss.h"
#include "sound.h"

EnemyData g_Enemies[MAX_ENEMIES];

void InitEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        g_Enemies[i].active = false;
    }
}

void SpawnEnemy(float x,
    float y, int hp,
    float speedX, float speedY)
{
	if (IsBossActive())return;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!g_Enemies[i].active) {
            g_Enemies[i].active = true;
            g_Enemies[i].posX = x;
            g_Enemies[i].posY = y;
            g_Enemies[i].hp = hp;
            g_Enemies[i].speedX = speedX;
            g_Enemies[i].speedY = speedY;
            g_Enemies[i].handle
                = LoadGraph("enemy.png");
            g_Enemies[i].width = 64;
            g_Enemies[i].height = 64;
            break;
        }
    }
}

void UpdateEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!g_Enemies[i].active) continue;

        // 移動
        g_Enemies[i].posX 
            += g_Enemies[i].speedX;

        g_Enemies[i].posY
            += g_Enemies[i].speedY;

        // 画面外に出たら消す
        if (g_Enemies[i].posX 
            < -100 || g_Enemies[i].posX > 1700 ||
            
            g_Enemies[i].posY < -100 
            || g_Enemies[i].posY > 900)
        {
            g_Enemies[i].active = false;
        }
    }
}

void DrawEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (!g_Enemies[i].active) continue;
        DrawGraph((int)g_Enemies[i].posX, 
            (int)g_Enemies[i].posY,
            g_Enemies[i].handle, TRUE);
    }
}

void KillEnemy(int index)
{
    if (!g_Enemies[index].active) return;

    g_Enemies[index].active = false;

    // メダルドロップ
    AddMedarus(1);

    // エフェクトとかSE
	  PlaySE(SE_ENEMY_DEAD);
}

void ClearAllEnemies()
{
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        g_Enemies[i].active = false; // 全部消す
    }
}

