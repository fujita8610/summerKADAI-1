#pragma once
#include "EnemyParameter.h"

// �G�S�̂̏���
void InitEnemy();
void LoadEnemy();
void StepEnemy();
void UpdateEnemy();
void DrawEnemy();
void FinEnemy();

// �G��z�u
void StepEnemySpawnSystem();

// �w�肵���G�l�~�[�̌��j����Ԃ�
int GetEnemyDestroyNum(EnemyType type);
