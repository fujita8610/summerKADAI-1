#pragma once
#include "AnimationEffectParameter.h"

// �e�֐��̐錾
void InitAnimationEffect();
void LoadAnimationEffect();
void StepAnimationEffect();
void UpdateAnimationEffect();
void DrawAnimationEffect();
void FinAnimationEffect();

// �G�t�F�N�g�J�n
void StartAnimationEffect(AnimationEffectType type, float posX, float posY, int interval);

