#include "DxLib.h"
#include "BackGround.h"

#define BACK_GROUND_WIDTH	(1600)
#define BACK_GROUND_HEIGHT	(900)

// �w�i�p�̃f�[�^
struct BackGroundData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
};
BackGroundData g_BackGroundData[BACK_GROUND_LAYER_MAX] = { 0 };

void InitBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		g_BackGroundData[i].handle = 0;
		g_BackGroundData[i].posX = 0.0f;
		g_BackGroundData[i].posY = 0.0f;
		g_BackGroundData[i].moveX = 0.0f;
		g_BackGroundData[i].moveY = 0.0f;
	}
}

void LoadBackGround(const char* path, BackGroundLayer layer)
{
	g_BackGroundData[layer].handle = LoadGraph(path);
}

void StepBackGround()
{
}

void UpdateBackGround()
{
	// �ړ�
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		g_BackGroundData[i].posX += g_BackGroundData[i].moveX;
		g_BackGroundData[i].posY += g_BackGroundData[i].moveY;

		// �X�N���[���̃��[�v
		if (g_BackGroundData[i].posX > BACK_GROUND_WIDTH)
		{
			g_BackGroundData[i].posX -= BACK_GROUND_WIDTH;
		}
		if (g_BackGroundData[i].posX < -BACK_GROUND_WIDTH)
		{
			g_BackGroundData[i].posX += BACK_GROUND_WIDTH;
		}
		if (g_BackGroundData[i].posY > BACK_GROUND_HEIGHT)
		{
			g_BackGroundData[i].posY -= BACK_GROUND_HEIGHT;
		}
		if (g_BackGroundData[i].posY < -BACK_GROUND_HEIGHT)
		{
			g_BackGroundData[i].posY += BACK_GROUND_HEIGHT;
		}
	}
}

void DrawBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		DrawGraph((int)g_BackGroundData[i].posX, (int)g_BackGroundData[i].posY, (int)g_BackGroundData[i].handle, TRUE);

		// ���ɃX�N���[�����Ă�����E���ɂ����ꖇ�`��
		if (g_BackGroundData[i].moveX < 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].posX + BACK_GROUND_WIDTH, (int)g_BackGroundData[i].posY, (int)g_BackGroundData[i].handle, TRUE);
		}
		// �E�ɃX�N���[�����Ă����獶���ɂ����ꖇ�`��
		if (g_BackGroundData[i].moveX > 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].posX - BACK_GROUND_WIDTH, (int)g_BackGroundData[i].posY, (int)g_BackGroundData[i].handle, TRUE);
		}
		// ��ɃX�N���[�����Ă����牺���ɂ����ꖇ�`��
		if (g_BackGroundData[i].moveY > 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].posX, (int)g_BackGroundData[i].posY - BACK_GROUND_HEIGHT, (int)g_BackGroundData[i].handle, TRUE);
		}
		// ���ɃX�N���[�����Ă�����㑤�ɂ����ꖇ�`��
		if (g_BackGroundData[i].moveY < 0.0f)
		{
			DrawGraph((int)g_BackGroundData[i].posX, (int)g_BackGroundData[i].posY + BACK_GROUND_HEIGHT, (int)g_BackGroundData[i].handle, TRUE);
		}
	}
}



void FinBackGround()
{
	for (int i = 0; i < BACK_GROUND_LAYER_MAX; i++)
	{
		DeleteGraph(g_BackGroundData[i].handle);
	}
}

void SetBackGroundMove(float moveX, float moveY, BackGroundLayer layer)
{
	g_BackGroundData[layer].moveX = moveX;
	g_BackGroundData[layer].moveY = moveY;
}
