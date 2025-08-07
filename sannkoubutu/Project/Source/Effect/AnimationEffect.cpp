#include "DxLib.h"
#include "AnimationEffect.h"
#include "AnimationEffectParameter.h"

#define ANIMATION_EFFECT_MAX 255

struct AnimationEffectData
{
	bool active;
	int handle;
	int nowFrame;
	int frameNum;
	int frameWidth;
	int frameHeight;
	int timer;
	int interval;
	float posX;
	float posY;
};
AnimationEffectData g_AnimationEffectData[ANIMATION_EFFECT_MAX] = { 0 };

int g_AnimationEffectHandle[ANIMATION_EFFECT_TYPE_MAX];

void InitAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		effect->active = false;
		effect->handle = 0;
		effect->nowFrame = 0;
		effect->frameNum = 0;
		effect->frameWidth = 0;
		effect->frameHeight = 0;
		effect->timer = 0;
		effect->posX = 0.0f;
		effect->posY = 0.0f;
	}
}

void LoadAnimationEffect()
{
	g_AnimationEffectHandle[PLAYER_NORMAL_SHOT_HIT] = LoadGraph("Data/Effect/PlayerNormalBulletHit.png");
	g_AnimationEffectHandle[PLAYER_DEAD] = LoadGraph("Data/Effect/PlayerDead.png");
	g_AnimationEffectHandle[ENEMY_DEAD] = LoadGraph("Data/Effect/EnemyDead.png");
	g_AnimationEffectHandle[ENEMY_BULLET_HIT] = LoadGraph("Data/Effect/KapuBulletHit.png");
}

void StepAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		if (!effect->active) continue;

		// ���̃R�}�֐i�߂邩
		if (effect->timer <= 0)
		{
			// ���̃R�}��
			effect->nowFrame++;
			// �^�C�}�[���Z�b�g
			effect->timer = effect->interval;

			// �S�R�}�\�����I��������A�N�e�B�u
			if (effect->nowFrame >= effect->frameNum)
			{
				effect->active = false;

				// ����ȏ㏈������K�v�Ȃ�
				continue;
			}
		}

		effect->timer--;
	}
}

void UpdateAnimationEffect()
{
}

void DrawAnimationEffect()
{
	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		if (!effect->active)continue;

		// �R�}�̐؂���ʒu�v�Z�i���P�s�̉摜�̑z��j
		int frameX = effect->frameWidth * effect->nowFrame;

		// �摜����\������R�}�̕��������`��
		DrawRectGraph((int)effect->posX, (int)effect->posY, frameX, 0, effect->frameWidth, effect->frameHeight, effect->handle, TRUE);
	}
}

void FinAnimationEffect()
{
	for (int i = 0; i < ANIMATION_EFFECT_TYPE_MAX; i++)
	{
		DeleteGraph(g_AnimationEffectHandle[i]);
	}
}

void StartAnimationEffect(AnimationEffectType type, float posX, float posY, int interval)
{
	// �}�X�^�[�p�����擾
	AnimationEffectMasterParameter param = ANIM_EFFECT_MASTER_PARAM[type];

	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		// ���g�p�̃G�t�F�N�g��T��
		if (!effect->active)
		{
			// �A�N�e�B�u
			effect->active = true;

			// ���W�ݒ�
			effect->posX = posX;
			effect->posY = posY;

			// �C���^�[�o���ݒ�
			effect->interval = interval;

			// �^�C�}�[�ݒ�
			effect->timer = effect->interval;

			// �摜�n���h��
			effect->handle = g_AnimationEffectHandle[type];

			// 0�R�}�ڂɂ���
			effect->nowFrame = 0;

			// �R�}��
			effect->frameNum = param.frameNum;

			// 1�R�}�̃T�C�Y
			effect->frameWidth = param.frameWidth;
			effect->frameHeight = param.frameHeight;

			break;
		}
	}
}
