// Enemy.h
#pragma once
#include "DxLib.h"

struct EnemyData {
    bool active;
    float posX, posY;
    float speedX, speedY;
    int hp;
    int handle;   // ‰æ‘œ
    int width, height;
};

#define MAX_ENEMIES (64)

void InitEnemies();
void SpawnEnemy(float x, float y, int hp, float speedX, float speedY);
void UpdateEnemies();
void DrawEnemies();
void KillEnemy(int index);
void ClearAllEnemies();

EnemyData* GetEnemies();