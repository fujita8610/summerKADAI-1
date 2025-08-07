#include "DxLib.h"
#include "Kapu.h"
#include "EnemyParameter.h"
#include "../GameSetting/GameSetting.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Bullet/BulletManager.h"
#include "../Sound/SoundManager.h"

#define ENEMY_KAPU_CHANGE_MOVE_TIME (150)	// �����]������܂ł̎���
#define ENEMY_KAPU_SPEED	(-20.0f)
#define ENEMY_KAPU_BREAK	(0.5f) 

#define ENEMY_KAPU_ACTIVE_AREA_LEFT	(-100)
#define ENEMY_KAPU_ACTIVE_AREA_TOP		(-100)
#define ENEMY_KAPU_ACTIVE_AREA_RIGHT	(2000)
#define ENEMY_KAPU_ACTIVE_AREA_BOTTOM	(1000)

// ���j���̃X�R�A
#define ENEMY_KAPU_SCORE (1000)

// ���S�G�t�F�N�g�̃C���^�[�o��
#define ENEMY_KAPU_DEAD_EFFECT_INTERVAL (3)

// ���S�G�t�F�N�g�ʒu�I�t�Z�b�g
#define ENEMY_KAPU_DEAD_EFFECT_OFFSET (16.0f)

// �o���b�g�֘A
#define ENEMY_KAPU_BULLET_INTERVAL	(60)
#define ENEMY_KAPU_BULLET_SPEED		(10.0f)
#define ENEMY_KAPU_BULLET_LIFE		(300)

// HP
#define ENEMY_KAPU_HP (10)

// �ϐ�
EnemyKapuData g_KapuData[ENEMY_KAPU_MAX] = { 0 };

// �摜�n���h��
int g_EnemyKapuHandle = 0;

// ���j������
int g_EnemyKapuDestroyNum = 0;

void InitKapu()
{
	// ���ʕϐ�������
	g_EnemyKapuHandle = 0;
	g_EnemyKapuDestroyNum = 0;

	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		kapu->handle = 0;
		kapu->bulletTimer = 0;
		kapu->hp = 0;

		kapu->posX = 0.0f;
		kapu->posY = 0.0f;
		kapu->moveX = 0.0f;
		kapu->moveY = 0.0f;

		kapu->active = false;
		kapu->isMoveChange = false;
	}
}

void LoadKapu()
{
	g_EnemyKapuHandle = LoadGraph("Data/Enemy/Kapu.png");
}

void StepKapu()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// ����ł����珈�����Ȃ�
		if (!kapu->active) continue;

		// ���X�Ɍ���
		kapu->moveX += ENEMY_KAPU_BREAK;

		// �ړ��ʂ����]�������ɂȂ�����~�߂�
		if (kapu->moveX > 0.0f)
		{
			kapu->moveX = 0.0f;
		}

		// �o���b�g�^�C�}�[���J�E���g�_�E��
		kapu->bulletTimer--;
	}
}

void UpdateKapu()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// ����ł����珈�����Ȃ�
		if (!kapu->active) continue;

		// �ړ�����
		kapu->posX += kapu->moveX;
		kapu->posY += kapu->moveY;

		// �C���^�[�o�����ԂɂȂ�����e����
		if (kapu->bulletTimer <= 0)
		{
			// �e�̔��˃f�[�^�ݒ�
			FireBulletData fireData =
			{
				ENEMY_KAPU_BULLET_LIFE,
				kapu->posX,
				kapu->posY + 20.0f,
				-ENEMY_KAPU_BULLET_SPEED,
				0.0f
			};
			// ����
			FireBullet(BULLET_CATEGORY_STRAIGHT, STRAIGHT_BULLET_TYPE_KAPU, fireData, BULLET_COLLISION_TAG_ENEMY);
			
			// �^�C�}�[���Z�b�g
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;
		}

		// ��ʊO�ɂł��玀�S
		if (kapu->posX <= ENEMY_KAPU_ACTIVE_AREA_LEFT || kapu->posX >= ENEMY_KAPU_ACTIVE_AREA_RIGHT)
		{
			kapu->active = false;
		}
		else if (kapu->posY <= ENEMY_KAPU_ACTIVE_AREA_TOP || kapu->posY >= ENEMY_KAPU_ACTIVE_AREA_BOTTOM)
		{
			kapu->active = false;
		}

	}

}

void DrawKapu()
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// ����ł����珈�����Ȃ�
		if (!kapu->active) continue;

		DrawGraph((int)kapu->posX, (int)kapu->posY, kapu->handle, TRUE);
	}
}

void FinKapu()
{
	DeleteGraph(g_EnemyKapuHandle);
}

EnemyKapuData* GetKapu()
{
	// �z��̐擪�A�h���X��ԋp����
	return g_KapuData;
}

void CreateKapu(float posX, float posY, const EnemyParameter* param)
{
	// �|�C���^���g���Ĕz����Q�Ƃ���
	EnemyKapuData* kapu = g_KapuData;
	for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
	{
		// ���g�p��Kapu��T��
		if (!kapu->active)
		{
			// �����t���O�𗧂Ă�
			kapu->active = true;

			// �o���b�g�^�C�}�[��ݒ�
			kapu->bulletTimer = ENEMY_KAPU_BULLET_INTERVAL;

			// HP
			kapu->hp = ENEMY_KAPU_HP;

			// �����]���t���O��܂�
			kapu->isMoveChange = false;

			// �摜�n���h���ݒ�
			kapu->handle = g_EnemyKapuHandle;

			// ���W�ݒ�
			kapu->posX = posX;
			kapu->posY = posY;

			// �ړ��ʐݒ�
			kapu->moveX = ENEMY_KAPU_SPEED;	// ����
			kapu->moveY = 0.0f;

			// �p�����[�^�ݒ�
			kapu->param = param;

			break;
		}
	}
}

void KapuHitPlayer(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// �Փ˂����玀�S
	kapu->active = false;

	// ���S�G�t�F�N�g
	StartAnimationEffect(ENEMY_DEAD, kapu->posX, kapu->posY, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

	// ���j�������Z
	g_EnemyKapuDestroyNum++;
}

void KapuHitPlayerBullet(int index)
{
	EnemyKapuData* kapu = &g_KapuData[index];

	// �_���[�W
	kapu->hp--;

	// HP��0�ɂȂ����玀�S
	if (kapu->hp <= 0)
	{
		kapu->active = false;

		// ���S�G�t�F�N�g
		StartAnimationEffect(ENEMY_DEAD, kapu->posX + ENEMY_KAPU_DEAD_EFFECT_OFFSET, kapu->posY + ENEMY_KAPU_DEAD_EFFECT_OFFSET, ENEMY_KAPU_DEAD_EFFECT_INTERVAL);

		// �X�R�A�����Z
		int score = GetScore() + ENEMY_KAPU_SCORE;
		SetScore(score);

		// ���SSE�Đ�
		PlaySE(SE_ENEMY_DEAD);

		// ���j�������Z
		g_EnemyKapuDestroyNum++;
	}
}

// ���j�����擾
int GetKapuDestroyNum()
{
	return g_EnemyKapuDestroyNum;
}
