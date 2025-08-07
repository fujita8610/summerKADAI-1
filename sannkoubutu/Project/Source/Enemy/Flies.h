#pragma once
#include "EnemyParameter.h"

// 関数のプロトタイプ宣言
void InitFlies();
void LoadFlies();
void StepFlies();
void UpdateFlies();
void DrawFlies();
void FinFlies();

// Fliesを生成
void CreateFlies(float posX, float posY, const EnemyParameter* param);

// Flies取得
EnemyFliesData* GetFlies();

// 当たり判定関連
void FliesHitPlayer(int index);

// 当たり判定関連
void FliesHitPlayerBullet(int index);
