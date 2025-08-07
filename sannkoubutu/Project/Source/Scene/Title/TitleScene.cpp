#include "DxLib.h"
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../BackGround/BackGround.h"
#include "../../Sound/SoundManager.h"
#include <math.h>

// �w�i�̃X�s�[�h
#define BACK_GROUND_SPEED (-0.3f)

// �^�C�g���̈ʒu
#define TITLE_POS_X (280)
#define TITLE_POS_Y (130)

// PressZKey�̈ʒu
#define PRESS_Z_KEY_POS_X (500)
#define PRESS_Z_KEY_POS_Y (530)

// PressZKey�̓_�ŃX�s�[�h
#define PRESS_Z_KEY_BLINK_SPEED (0.04f)

// �摜�n���h��
int g_BGHandle = 0;
int g_TitleHandle = 0;
int g_PressZKeyHandle = 0;

// PressZKye�_�ŗp�ϐ�
float g_PressZKeyAlpha = 0.0f;	// �A���t�@�l
float g_PressZKeyRadian = 0.0f;	// cos�֐��ɓn�����W�A���l

void InitTitleScene()
{
	g_BGHandle = 0;
	g_TitleHandle = 0;
	g_PressZKeyHandle = 0;
	g_PressZKeyAlpha = 0.0f;
	g_PressZKeyRadian = 0.0f;

	// �w�i������
	InitBackGround();
}

void LoadTitleScene()
{
	// �w�i�͔w�i�V�X�e�����g��
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// �w�i�����ɃX�N���[��������
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// �e�摜�����[�h
	g_BGHandle = LoadGraph("Data/Title/TitleBG.png");
	g_TitleHandle = LoadGraph("Data/Title/TitleText.png");
	g_PressZKeyHandle = LoadGraph("Data/Title/TitlePressZKey.png");
}

void StartTitleScene()
{
	// BGM�Đ�
	PlayBGM(BGM_TITLE);
}


void StepTitleScene()
{
	// sin�g�̒l����PressZKey�̃A���t�@�l�i�����x�j���v�Z����
	// sinf��-1�`1�̒l��ԋp����̂ŉ��H����0�`1�̒l�ɂ��Ă���
	g_PressZKeyAlpha = (sinf(g_PressZKeyRadian) + 1) / 2;

	// ���W�A���l��_�ő��x�ŉ��Z
	g_PressZKeyRadian += PRESS_Z_KEY_BLINK_SPEED;

	// ���W�A���l��0�`2�΂����[�v������
	if (g_PressZKeyRadian > DX_TWO_PI_F)
	{
		g_PressZKeyRadian -= DX_TWO_PI_F;
	}

	// Z�L�[�������ꂽ��v���C�V�[����
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_PLAY);
	}

	// �w�i�X�e�b�v
	StepBackGround();
}

void UpdateTitleScene()
{
	// �w�i�X�V
	UpdateBackGround();
}

void DrawTitleScene()
{
	// �w�i�`��
	DrawBackGround();

	// �^�C�g���`��
	DrawGraph(TITLE_POS_X, TITLE_POS_Y, g_TitleHandle, TRUE);

	// �_�ł̂��߂Ƀu�����h���[�h��ݒ肷��(DXLib�̎d�l��0�`255�Ŏw�肷��̂ŉ��H����)
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(g_PressZKeyAlpha * 255));

	// Press Z Key �`��
	DrawGraph(PRESS_Z_KEY_POS_X, PRESS_Z_KEY_POS_Y, g_PressZKeyHandle, TRUE);

	// �u�����h���[�h��߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void FinTitleScene()
{
	// �w�i�I��
	FinBackGround();

	// �e�摜���폜
	DeleteGraph(g_TitleHandle);
	DeleteGraph(g_PressZKeyHandle);

	// BGM��~
	StopBGM(BGM_TITLE);
}
