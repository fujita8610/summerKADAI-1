#pragma once
#include "EnemyParameter.h"

// �֐��̃v���g�^�C�v�錾
void InitFlies();
void LoadFlies();
void StepFlies();
void UpdateFlies();
void DrawFlies();
void FinFlies();

// Flies�𐶐�
void CreateFlies(float posX, float posY, const EnemyParameter* param);

// Flies�擾
EnemyFliesData* GetFlies();

// �����蔻��֘A
void FliesHitPlayer(int index);

// �����蔻��֘A
void FliesHitPlayerBullet(int index);
