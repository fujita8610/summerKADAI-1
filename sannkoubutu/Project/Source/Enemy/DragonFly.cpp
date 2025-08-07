#include "DxLib.h"
#include "DragonFly.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"

// ���j���̃X�R�A
#define ENEMY_DRAGON_FLY_SCORE (300)

#define ENEMY_DRAGON_FLY_MOVE_X_MAX	(25.0f)	// �ő�ړ����x�i�����j
#define ENEMY_DRAGON_FLY_BREAK_X	(1.5f)	// �u���[�L�́i�����́j
#define ENEMY_DRAGON_FLY_MOVE_Y_MAX	(7.0f)	// �ő�ړ����x�i�����j
#define ENEMY_DRAGON_FLY_BREAK_Y	(0.30f)	// �u���[�L�́i�����́j

// �����ł���G���A
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_TOP	(-100)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_DRAGON_FLY_ACTIVE_AREA_BOTTOM	(1000)

// �Ĉړ��܂ł̃C���^�[�o��
#define ENEMY_DRAGON_FLY_MOVE_INTERVAL (90)

// ���S�G�t�F�N�g�̃C���^�[�o��
#define ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL	(3)

// �ϐ�
EnemyDragonFlyData g_DragonFlyData[ENEMY_DRAGON_FLY_MAX] = { 0 };

// �摜�n���h��
int g_EnemyDragonFlyHandle = 0;

void InitDragonFly()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		dragonFly->posX = 0.0f;
		dragonFly->posY = 0.0f;
		dragonFly->moveX = 0.0f;
		dragonFly->moveY = 0.0f;

		dragonFly->active = false;
		dragonFly->isMoveChange = false;

		dragonFly->directionY = 0;
	}
}

void LoadDragonFly()
{
	g_EnemyDragonFlyHandle = LoadGraph("Data/Enemy/DragonFly.png");
}

void StepDragonFly()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// ����ł����珈�����Ȃ�
		if (!dragonFly->active) continue;

		// ���X�Ɍ���
		dragonFly->moveX += ENEMY_DRAGON_FLY_BREAK_X;
		// ���Ε����ɂ͂����Ȃ�
		if (dragonFly->moveX > 0.0f)
		{
			dragonFly->moveX = 0.0f;
		}

		// �㉺�͌��݂ɂȂ�̂Ō�������������
		if (dragonFly->directionY > 0)
		{
			dragonFly->moveY -= ENEMY_DRAGON_FLY_BREAK_Y;
			if (dragonFly->moveY < 0.0f)
			{
				dragonFly->moveY = 0.0f;
			}
		}
		else if(dragonFly->directionY < 0)
		{
			dragonFly->moveY += ENEMY_DRAGON_FLY_BREAK_Y;
			if (dragonFly->moveY > 0.0f)
			{
				dragonFly->moveY = 0.0f;
			}
		}

		// �^�C�}�[��0�ɂȂ�����Ĉړ�
		if (dragonFly->timer <= 0)
		{
			dragonFly->timer = ENEMY_DRAGON_FLY_MOVE_INTERVAL;

			// �������ړ��ʂɐݒ�
			dragonFly->moveX = -ENEMY_DRAGON_FLY_MOVE_X_MAX;	// �K����
			// �㉺�͌��݂�
			dragonFly->directionY = -dragonFly->directionY;
			dragonFly->moveY = ENEMY_DRAGON_FLY_MOVE_Y_MAX * dragonFly->directionY;
		}

		dragonFly->timer--;
	}
}

void UpdateDragonFly()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// ����ł����珈�����Ȃ�
		if (!dragonFly->active) continue;

		dragonFly->posX += dragonFly->moveX;
		dragonFly->posY += dragonFly->moveY;

		// ��ʊO�ɂł��玀�S
		if (dragonFly->posX <= ENEMY_DRAGON_FLY_ACTIVE_AREA_LEFT || dragonFly->posX >= ENEMY_DRAGON_FLY_ACTIVE_AREA_RIGHT)
		{
			dragonFly->active = false;
		}
		else if (dragonFly->posY <= ENEMY_DRAGON_FLY_ACTIVE_AREA_TOP || dragonFly->posY >= ENEMY_DRAGON_FLY_ACTIVE_AREA_BOTTOM)
		{
			dragonFly->active = false;
		}

	}

}

void DrawDragonFly()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// ����ł����珈�����Ȃ�
		if (!dragonFly->active) continue;

		DrawGraph((int)dragonFly->posX, (int)dragonFly->posY, dragonFly->handle, TRUE);
	}
}

void FinDragonFly()
{
	DeleteGraph(g_EnemyDragonFlyHandle);
}

EnemyDragonFlyData* GetDragonFly()
{
	// �z��̐擪�A�h���X��ԋp����
	return g_DragonFlyData;
}

void CreateDragonFly(float posX, float posY, const EnemyParameter* param)
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyDragonFlyData* dragonFly = g_DragonFlyData;
	for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
	{
		// ���g�p��DragonFly��T��
		if (!dragonFly->active)
		{
			// �����t���O�𗧂Ă�
			dragonFly->active = true;

			// �����]���t���O��܂�
			dragonFly->isMoveChange = false;

			// �摜�n���h���ݒ�
			dragonFly->handle = g_EnemyDragonFlyHandle;

			// ���W�ݒ�
			dragonFly->posX = posX;
			dragonFly->posY = posY;

			// �ړ��ʃ��Z�b�g
			dragonFly->moveX = 0.0f;
			dragonFly->moveY = 0.0f;

			// �^�C�}�[���Z�b�g
			dragonFly->timer = 0;

			// �p�����[�^�ݒ�
			dragonFly->param = param;

			// Y�ړ������ݒ�
			dragonFly->directionY = 1;

			break;
		}
	}
}

void DragonFlyHitPlayer(int index)
{
	EnemyDragonFlyData* dragonFly = &g_DragonFlyData[index];

	// �Փ˂����玀�S
	dragonFly->active = false;

	// ���S�G�t�F�N�g
	StartAnimationEffect(ENEMY_DEAD, dragonFly->posX, dragonFly->posY, ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL);
}

void DragonFlyHitPlayerBullet(int index)
{
	EnemyDragonFlyData* dragonFly = &g_DragonFlyData[index];

	// �Փ˂����玀�S
	dragonFly->active = false;

	// �X�R�A���Z
	int score = GetScore() + ENEMY_DRAGON_FLY_SCORE;
	SetScore(score);

	// ���S�G�t�F�N�g
	StartAnimationEffect(ENEMY_DEAD, dragonFly->posX, dragonFly->posY, ENEMY_DRAGON_FLY_DEAD_EFFECT_INTERVAL);

	// ���SSE�Đ�
	PlaySE(SE_ENEMY_DEAD);
}

