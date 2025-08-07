#pragma once
#include "EnemyParameter.h"

// �֐��̃v���g�^�C�v�錾
void InitDragonFly();
void LoadDragonFly();
void StepDragonFly();
void UpdateDragonFly();
void DrawDragonFly();
void FinDragonFly();

// DragonFly�𐶐�
void CreateDragonFly(float posX, float posY, const EnemyParameter* param);

// DragonFly�擾
EnemyDragonFlyData* GetDragonFly();

// �����蔻��֘A
void DragonFlyHitPlayer(int index);

// �����蔻��֘A
void DragonFlyHitPlayerBullet(int index);
