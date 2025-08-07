#include "DxLib.h"
#include "UIImage.h"

#define UI_IMAGE_MAX 32

// UIImage�f�[�^
UIImageData g_UIImageData[UI_IMAGE_MAX] = { 0 };

// �摜�n���h���ۑ��z��
int g_UIImageHandle[UI_IMAGE_TYPE_MAX] = { 0 };

void InitUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < UI_IMAGE_MAX; i++, ui++)
	{
		ui->active = false;
		ui->handle = 0;
		ui->posX = 0.0f;
		ui->posY = 0.0f;
	}
}

void LoadUIImage()
{
	// �v���C�V�[��
	g_UIImageHandle[UI_IMAGE_PLAY_FOOTER_FRAME] = LoadGraph("Data/UI/PlayFooterFrame.png");
	g_UIImageHandle[UI_IMAGE_HEART] = LoadGraph("Data/UI/Life.png");
	g_UIImageHandle[UI_IMAGE_TARGET_KAPU] = LoadGraph("Data/Enemy/Kapu.png");
}

void StepUIImage()
{
}

void UpdateUIImage()
{
}

void DrawUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < UI_IMAGE_MAX; i++, ui++)
	{
		if (!ui->active) continue;

		DrawGraph((int)ui->posX, (int)ui->posY, ui->handle, TRUE);
	}
}

void FinUIImage()
{
	for (int i = 0; i < UI_IMAGE_TYPE_MAX; i++)
	{
		DeleteGraph(g_UIImageHandle[i]);
	}
}

// UIImage�𐶐�����
void CreateUIImage(UIImageType type, float posX, float posY)
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < UI_IMAGE_MAX; i++, ui++)
	{
		// ���g�p��UI��T��
		if (!ui->active)
		{
			// �A�N�e�B�u
			ui->active = true;

			// �摜�n���h��
			ui->handle = g_UIImageHandle[type];

			// ���W
			ui->posX = posX;
			ui->posY = posY;

			break;
		}
	}
}

void ResetUIImage()
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < UI_IMAGE_MAX; i++, ui++)
	{
		ui->active = false;
	}
}
