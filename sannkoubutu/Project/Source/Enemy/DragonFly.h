#pragma once
#include "EnemyParameter.h"

// 関数のプロトタイプ宣言
void InitDragonFly();
void LoadDragonFly();
void StepDragonFly();
void UpdateDragonFly();
void DrawDragonFly();
void FinDragonFly();

// DragonFlyを生成
void CreateDragonFly(float posX, float posY, const EnemyParameter* param);

// DragonFly取得
EnemyDragonFlyData* GetDragonFly();

// 当たり判定関連
void DragonFlyHitPlayer(int index);

// 当たり判定関連
void DragonFlyHitPlayerBullet(int index);
