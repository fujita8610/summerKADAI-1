#pragma once
#include "EnemyParameter.h"

// �֐��̃v���g�^�C�v�錾
void InitKapu();
void LoadKapu();
void StepKapu();
void UpdateKapu();
void DrawKapu();
void FinKapu();

// Kapu�𐶐�
void CreateKapu(float posX, float posY, const EnemyParameter* param);

// Kapu�擾
EnemyKapuData* GetKapu();

// �����蔻��֘A
void KapuHitPlayer(int index);

// �����蔻��֘A
void KapuHitPlayerBullet(int index);

// ���j�����擾
int GetKapuDestroyNum();
