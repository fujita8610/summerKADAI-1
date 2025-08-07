#include "DxLib.h"
#include "Flies.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Sound/SoundManager.h"

#define ENEMY_FLIES_MOVE_SPEED	(5.0f)	// �ړ����x
#define ENEMY_FLIES_CHANGE_MOVE_TIME (150)	// �����]������܂ł̎���

#define ENEMY_FLIES_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_FLIES_ACTIVE_AREA_TOP		(-100)
#define ENEMY_FLIES_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_FLIES_ACTIVE_AREA_BOTTOM	(1000)

// ���j���̃X�R�A
#define ENEMY_FLIES_SCORE (100)

// ���S�G�t�F�N�g�̃C���^�[�o��
#define ENEMY_FLIES_DEAD_EFFECT_INTERVAL (3)

// �ϐ�
EnemyFliesData g_FliesData[ENEMY_FLIES_MAX] = { 0 };

// �摜�n���h��
int g_EnemyFliesHandle = 0;

void InitFlies()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		flies->posX = 0.0f;
		flies->posY = 0.0f;
		flies->moveX = 0.0f;
		flies->moveY = 0.0f;

		flies->active = false;
		flies->isMoveChange = false;
	}
}

void LoadFlies()
{
	g_EnemyFliesHandle = LoadGraph("Data/Enemy/Flies.png");
}

void StepFlies()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// ����ł����珈�����Ȃ�
		if (!flies->active) continue;

		// ���Ɉړ�
		flies->moveX = -ENEMY_FLIES_MOVE_SPEED;

		// �p�����[�^���ݒ肳��Ă��邩
		if (flies->param != nullptr)
		{
			// �܂������]�����Ă��Ȃ���
			if (!flies->isMoveChange)
			{
				// �����]������ʒu�܂ňړ�������
				if (flies->posX <= flies->param->moveChangePosX)
				{
					// ��ʏ㑤�ɂ���Ƃ��͉��A�����ɂ���Ƃ��͏�Ɉړ�
					flies->moveY = flies->posY < (SCREEN_HEIGHT / 2) ? ENEMY_FLIES_MOVE_SPEED : -ENEMY_FLIES_MOVE_SPEED;
					flies->isMoveChange = true;
				}
			}
		}
	}
}

void UpdateFlies()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// ����ł����珈�����Ȃ�
		if (!flies->active) continue;

		flies->posX += flies->moveX;
		flies->posY += flies->moveY;

		// ��ʊO�ɂł��玀�S
		if (flies->posX <= ENEMY_FLIES_ACTIVE_AREA_LEFT || flies->posX >= ENEMY_FLIES_ACTIVE_AREA_RIGHT)
		{
			flies->active = false;
		}
		else if (flies->posY <= ENEMY_FLIES_ACTIVE_AREA_TOP || flies->posY >= ENEMY_FLIES_ACTIVE_AREA_BOTTOM)
		{
			flies->active = false;
		}

	}

}

void DrawFlies()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// ����ł����珈�����Ȃ�
		if (!flies->active) continue;

		DrawGraph((int)flies->posX, (int)flies->posY, flies->handle, TRUE);
	}
}

void FinFlies()
{
	DeleteGraph(g_EnemyFliesHandle);
}

EnemyFliesData* GetFlies()
{
	// �z��̐擪�A�h���X��ԋp����
	return g_FliesData;
}

void CreateFlies(float posX, float posY, const EnemyParameter* param)
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyFliesData* flies = g_FliesData;
	for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
	{
		// ���g�p��Flies��T��
		if (!flies->active)
		{
			// �����t���O�𗧂Ă�
			flies->active = true;

			// �����]���t���O��܂�
			flies->isMoveChange = false;

			// �摜�n���h���ݒ�
			flies->handle = g_EnemyFliesHandle;

			// ���W�ݒ�
			flies->posX = posX;
			flies->posY = posY;

			// �ړ��ʃ��Z�b�g
			flies->moveX = 0.0f;
			flies->moveY = 0.0f;

			// �p�����[�^�ݒ�
			flies->param = param;

			break;
		}
	}
}

void FliesHitPlayer(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// �Փ˂����玀�S
	flies->active = false;

	// ���S�G�t�F�N�g
	StartAnimationEffect(ENEMY_DEAD, flies->posX, flies->posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);
}

void FliesHitPlayerBullet(int index)
{
	EnemyFliesData* flies = &g_FliesData[index];

	// �Փ˂����玀�S
	flies->active = false;

	// ���S�G�t�F�N�g
	StartAnimationEffect(ENEMY_DEAD, flies->posX, flies->posY, ENEMY_FLIES_DEAD_EFFECT_INTERVAL);

	// �X�R�A�����Z
	int score = GetScore() + ENEMY_FLIES_SCORE;
	SetScore(score);

	// ���SSE�Đ�
	PlaySE(SE_ENEMY_DEAD);
}

