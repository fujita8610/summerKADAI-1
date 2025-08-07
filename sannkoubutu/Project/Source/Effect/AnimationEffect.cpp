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

		// 次のコマへ進めるか
		if (effect->timer <= 0)
		{
			// 次のコマへ
			effect->nowFrame++;
			// タイマーリセット
			effect->timer = effect->interval;

			// 全コマ表示し終わったら非アクティブ
			if (effect->nowFrame >= effect->frameNum)
			{
				effect->active = false;

				// これ以上処理する必要なし
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

		// コマの切り取り位置計算（横１行の画像の想定）
		int frameX = effect->frameWidth * effect->nowFrame;

		// 画像から表示するコマの部分だけ描画
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
	// マスターパラム取得
	AnimationEffectMasterParameter param = ANIM_EFFECT_MASTER_PARAM[type];

	AnimationEffectData* effect = g_AnimationEffectData;
	for (int i = 0; i < ANIMATION_EFFECT_MAX; i++, effect++)
	{
		// 未使用のエフェクトを探す
		if (!effect->active)
		{
			// アクティブ
			effect->active = true;

			// 座標設定
			effect->posX = posX;
			effect->posY = posY;

			// インターバル設定
			effect->interval = interval;

			// タイマー設定
			effect->timer = effect->interval;

			// 画像ハンドル
			effect->handle = g_AnimationEffectHandle[type];

			// 0コマ目にする
			effect->nowFrame = 0;

			// コマ数
			effect->frameNum = param.frameNum;

			// 1コマのサイズ
			effect->frameWidth = param.frameWidth;
			effect->frameHeight = param.frameHeight;

			break;
		}
	}
}
