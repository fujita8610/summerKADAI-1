#pragma once
#include "AnimationEffectParameter.h"

// 各関数の宣言
void InitAnimationEffect();
void LoadAnimationEffect();
void StepAnimationEffect();
void UpdateAnimationEffect();
void DrawAnimationEffect();
void FinAnimationEffect();

// エフェクト開始
void StartAnimationEffect(AnimationEffectType type, float posX, float posY, int interval);

