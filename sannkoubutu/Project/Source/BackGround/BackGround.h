#pragma once

// �w�i���C���[�i�����������قǑO�ʁj
enum BackGroundLayer
{
	BACK_GROUND_LAYER_1,
	BACK_GROUND_LAYER_2,
	BACK_GROUND_LAYER_3,
	BACK_GROUND_LAYER_MAX,
};

// �֐��̃v���g�^�C�v�錾
void InitBackGround();
void LoadBackGround(const char* path, BackGroundLayer layer);
void StepBackGround();
void UpdateBackGround();
void DrawBackGround();
void FinBackGround();

// �w�i�̈ړ��ʐݒ�
void SetBackGroundMove(float moveX, float moveY, BackGroundLayer layer);
