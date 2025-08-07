#include "EnemyManager.h"
#include "Flies.h"
#include "DragonFly.h"
#include "Kapu.h"

int g_EnemySpawnTimer = 0;

void InitEnemy()
{
	// �G�l�~�[�o���^�C�}�[��������
	g_EnemySpawnTimer = 0;

	// �e�G�l�~�[��������
	// Flies
	InitFlies();
	// DragonFly
	InitDragonFly();
	// Kapu
	InitKapu();
}

void LoadEnemy()
{
	// �e�G�l�~�[�����[�h
	// Flies
	LoadFlies();
	// DragonFly
	LoadDragonFly();
	// Kapu
	LoadKapu();
}

void StepEnemy()
{
	// �e�G�l�~�[���X�e�b�v
	// Flies
	StepFlies();
	// DragonFly
	StepDragonFly();
	// Kapu
	StepKapu();
}

void UpdateEnemy()
{
	// �e�G�l�~�[���X�V
	// Flies
	UpdateFlies();
	// DragonFly
	UpdateDragonFly();
	// Kapu
	UpdateKapu();
}

void DrawEnemy()
{
	// �e�G�l�~�[��`��
	// Flies
	DrawFlies();
	// DragonFly
	DrawDragonFly();
	// Kapu
	DrawKapu();
}

void FinEnemy()
{
	// �e�G�l�~�[���I��
	// Flies
	FinFlies();
	// DragonFly
	FinDragonFly();
	// Kapu
	FinKapu();
}

void SpawnEnemy(const EnemySpawnData* spawnData)
{
	// �^�C�v���ƂɓG�𐶐����Ĕz�u
	switch (spawnData->type)
	{
	case ENEMY_TYPE_FLIES:
		CreateFlies(spawnData->posX, spawnData->posY, spawnData->param);
		break;

	case ENEMY_TYPE_DRAGON_FLY:
		CreateDragonFly(spawnData->posX, spawnData->posY, spawnData->param);
		break;

	case ENEMY_TYPE_KAPU:
		CreateKapu(spawnData->posX, spawnData->posY, spawnData->param);
		break;
	}
}

void StepEnemySpawnSystem()
{
	// �z��T�C�Y�����̔z��̌^�̃T�C�Y�Ŋ���Z����ƌ������Z�o�ł���
	int spawnDataNum = sizeof(ENEMY_SPAWN_DATA) / sizeof(EnemySpawnData);

	// �o���f�[�^���`�F�b�N
	const EnemySpawnData* spawn = ENEMY_SPAWN_DATA;
	for (int i = 0; i < spawnDataNum; i++, spawn++)
	{
		// �^�C�}�[����v������o��������
		if (spawn->spawnTime == g_EnemySpawnTimer)
		{
			SpawnEnemy(spawn);
		}
	}

	// �o���^�C�}�[��i�߂�
	g_EnemySpawnTimer++;
}

// �w�肵���G�l�~�[�̌��j����Ԃ�
int GetEnemyDestroyNum(EnemyType type)
{
	// Kapu�ȊO������
	switch (type)
	{
		case ENEMY_TYPE_FLIES:	return 0;
		case ENEMY_TYPE_DRAGON_FLY:	return 0;
		case ENEMY_TYPE_KAPU:	return GetKapuDestroyNum();
	}

	return 0;
}
