#pragma once

enum AnimationEffectType
{
	PLAYER_NORMAL_SHOT_HIT,
	PLAYER_DEAD,
	ENEMY_DEAD,
	ENEMY_BULLET_HIT,
	ANIMATION_EFFECT_TYPE_MAX
};

// エフェクトの種類毎のマスターパラメータ
// 画像の大きさ、コマ数など
struct AnimationEffectMasterParameter
{
	int frameNum;		// フレーム数
	int frameWidth;		// 1コマの横幅
	int frameHeight;	// 1コマの縦幅
};
const AnimationEffectMasterParameter ANIM_EFFECT_MASTER_PARAM[ANIMATION_EFFECT_TYPE_MAX] =
{
	12, 16, 16,	// PLAYER_NORMAL_SHOT_HIT
	12, 64, 64,	// PLAYER_DEAD
	3,  32, 32,	// ENEMY_DEAD
	12, 16, 16,	// ENEMY_BULLET_HIT
};
