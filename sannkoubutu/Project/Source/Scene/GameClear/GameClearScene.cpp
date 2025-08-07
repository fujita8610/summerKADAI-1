#include "DxLib.h"
#include "GameClearScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
#include "../../Sound/SoundManager.h"
#include "../../UI/UIText.h"
#include "../../Score/Score.h"
#include <stdio.h>

// �w�i�̃X�N���[�����x
#define BACK_GROUND_SPEED (-1.5)

// GameClear�����摜
int g_GameClearHandle = 0;

void InitGameClearScene()
{
	// �w�i������
	InitBackGround();

	// �����摜�n���h��������
	g_GameClearHandle = 0;
}

void LoadGameClearScene()
{
	// �w�i���[�h
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// �w�i�X�N���[��
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// GameClear�����摜
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClearScene()
{
	// �X�R�AUI����
	// �X�R�A
	CreateScoreUI(436.0f, 450.0f);
	// �n�C�X�R�A
	CreateHiScoreUI(390, 315);

	// BGM�Đ�
	PlayBGM(BGM_GAME_CLEAR);
}

void StepGameClearScene()
{
	// �w�i�X�e�b�v
	StepBackGround();

	// Z�L�[�Ń^�C�g���ɖ߂�
	if (IsTriggerKey(KEY_Z))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClearScene()
{
	// �w�i�X�V
	UpdateBackGround();
}

void DrawGameClearScene()
{
	// �w�i�`��
	DrawBackGround();

	// �����摜�`��
	DrawGraph(560, 110, g_GameClearHandle, TRUE);

	// �X�R�A�`��
	DrawUIText();
}

void FinGameClearScene()
{
	// �w�i�I��
	FinBackGround();

	// �����摜�폜
	DeleteGraph(g_GameClearHandle);

	// �X�R�AUI���Z�b�g
	ResetUIText();

	// BGM��~
	StopBGM(BGM_GAME_CLEAR);
}
