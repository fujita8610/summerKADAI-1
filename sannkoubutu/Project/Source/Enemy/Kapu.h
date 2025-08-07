#pragma once
#include "EnemyParameter.h"

// 関数のプロトタイプ宣言
void InitKapu();
void LoadKapu();
void StepKapu();
void UpdateKapu();
void DrawKapu();
void FinKapu();

// Kapuを生成
void CreateKapu(float posX, float posY, const EnemyParameter* param);

// Kapu取得
EnemyKapuData* GetKapu();

// 当たり判定関連
void KapuHitPlayer(int index);

// 当たり判定関連
void KapuHitPlayerBullet(int index);

// 撃破数を取得
int GetKapuDestroyNum();
