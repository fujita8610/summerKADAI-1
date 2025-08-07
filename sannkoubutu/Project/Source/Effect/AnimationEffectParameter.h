#pragma once

enum AnimationEffectType
{
	PLAYER_NORMAL_SHOT_HIT,
	PLAYER_DEAD,
	ENEMY_DEAD,
	ENEMY_BULLET_HIT,
	ANIMATION_EFFECT_TYPE_MAX
};

// �G�t�F�N�g�̎�ޖ��̃}�X�^�[�p�����[�^
// �摜�̑傫���A�R�}���Ȃ�
struct AnimationEffectMasterParameter
{
	int frameNum;		// �t���[����
	int frameWidth;		// 1�R�}�̉���
	int frameHeight;	// 1�R�}�̏c��
};
const AnimationEffectMasterParameter ANIM_EFFECT_MASTER_PARAM[ANIMATION_EFFECT_TYPE_MAX] =
{
	12, 16, 16,	// PLAYER_NORMAL_SHOT_HIT
	12, 64, 64,	// PLAYER_DEAD
	3,  32, 32,	// ENEMY_DEAD
	12, 16, 16,	// ENEMY_BULLET_HIT
};
