#include "DxLib.h"
#include "UIImage.h"

#define UI_IMAGE_MAX 32

// UIImageデータ
UIImageData g_UIImageData[UI_IMAGE_MAX] = { 0 };

// 画像ハンドル保存配列
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
	// プレイシーン
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

// UIImageを生成する
void CreateUIImage(UIImageType type, float posX, float posY)
{
	UIImageData* ui = g_UIImageData;
	for (int i = 0; i < UI_IMAGE_MAX; i++, ui++)
	{
		// 未使用のUIを探す
		if (!ui->active)
		{
			// アクティブ
			ui->active = true;

			// 画像ハンドル
			ui->handle = g_UIImageHandle[type];

			// 座標
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
