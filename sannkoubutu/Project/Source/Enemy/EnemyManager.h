#pragma once
#include "EnemyParameter.h"

// 敵全体の処理
void InitEnemy();
void LoadEnemy();
void StepEnemy();
void UpdateEnemy();
void DrawEnemy();
void FinEnemy();

// 敵を配置
void StepEnemySpawnSystem();

// 指定したエネミーの撃破数を返す
int GetEnemyDestroyNum(EnemyType type);
