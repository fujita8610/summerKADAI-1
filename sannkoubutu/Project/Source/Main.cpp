#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "FPS/FPS.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"
#include "UI/UIImage.h"
#include "UI/UIText.h"
#include "Sound/SoundManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �E�B���h�E���[�hON
	ChangeWindowMode(TRUE);

	// ��ʉ𑜓x�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �E�B���h�E�T�C�Y�ݒ�
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// ���ߐF�̐ݒ�
	SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// ���̓V�X�e����������
	InitInput();

	// UI�͂ǂ��ł��g���̂ŃQ�[���N�����ɏ������A���[�h
	InitUIImage();
	InitUIText();

	LoadUIImage();
	LoadUIText();

	// �T�E���h���ǂ��ł��g���̂ŃQ�[���N�����Ƀ��[�h
	LoadBGM();
	LoadSE();

	// FPS�����������
	InitFPS();

	// �Q�[���̃��C�����[�v
	while (ProcessMessage() >= 0)
	{
		// ���[�v�����O��1�~���b�~�߂�Ə��������肷��
		Sleep(1);

		// ��ʂ��N���A
		ClearDrawScreen();

		// ���͂��X�V
		UpdateInput();

		// �V�[���Ǘ��̍X�V
		SceneManagerUpdate();

		// ���̓V�X�e���̕`��
		DrawInput();

		// �G�X�P�[�v�L�[�ŏI��
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// FPS������X�V
		UpdateFPS();

		// FPS�`��
		DrawFPS();

		// 1�t���[��������������ҋ@
		FPSWait();

		// ��ʃt���b�v
		ScreenFlip();
	}

	// ���̓V�X�e���̏I��
	FinInput();

	// UI�I��
	FinUIImage();
	FinUIText();

	// �T�E���h�I��
	FinBGM();
	FinSE();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
