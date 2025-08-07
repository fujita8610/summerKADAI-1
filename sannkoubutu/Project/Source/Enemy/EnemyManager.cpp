#include "EnemyManager.h"
#include "Flies.h"
#include "DragonFly.h"
#include "Kapu.h"

int g_EnemySpawnTimer = 0;

void InitEnemy()
{
	// エネミー出現タイマーを初期化
	g_EnemySpawnTimer = 0;

	// 各エネミーを初期化
	// Flies
	InitFlies();
	// DragonFly
	InitDragonFly();
	// Kapu
	InitKapu();
}

void LoadEnemy()
{
	// 各エネミーをロード
	// Flies
	LoadFlies();
	// DragonFly
	LoadDragonFly();
	// Kapu
	LoadKapu();
}

void StepEnemy()
{
	// 各エネミーをステップ
	// Flies
	StepFlies();
	// DragonFly
	StepDragonFly();
	// Kapu
	StepKapu();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	// Flies
	UpdateFlies();
	// DragonFly
	UpdateDragonFly();
	// Kapu
	UpdateKapu();
}

void DrawEnemy()
{
	// 各エネミーを描画
	// Flies
	DrawFlies();
	// DragonFly
	DrawDragonFly();
	// Kapu
	DrawKapu();
}

void FinEnemy()
{
	// 各エネミーを終了
	// Flies
	FinFlies();
	// DragonFly
	FinDragonFly();
	// Kapu
	FinKapu();
}

void SpawnEnemy(const EnemySpawnData* spawnData)
{
	// タイプごとに敵を生成して配置
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
	// 配列サイズをその配列の型のサイズで割り算すると件数を算出できる
	int spawnDataNum = sizeof(ENEMY_SPAWN_DATA) / sizeof(EnemySpawnData);

	// 出現データをチェック
	const EnemySpawnData* spawn = ENEMY_SPAWN_DATA;
	for (int i = 0; i < spawnDataNum; i++, spawn++)
	{
		// タイマーが一致したら出現させる
		if (spawn->spawnTime == g_EnemySpawnTimer)
		{
			SpawnEnemy(spawn);
		}
	}

	// 出現タイマーを進める
	g_EnemySpawnTimer++;
}

// 指定したエネミーの撃破数を返す
int GetEnemyDestroyNum(EnemyType type)
{
	// Kapu以外未実装
	switch (type)
	{
		case ENEMY_TYPE_FLIES:	return 0;
		case ENEMY_TYPE_DRAGON_FLY:	return 0;
		case ENEMY_TYPE_KAPU:	return GetKapuDestroyNum();
	}

	return 0;
}
