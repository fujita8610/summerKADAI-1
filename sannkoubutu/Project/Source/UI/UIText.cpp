#include "DxLib.h"
#include "UIText.h"
#include <string.h>

#define UI_TEXT_MAX (32)

// UIText�f�[�^
UITextData g_UITextData[UI_TEXT_MAX] = { 0 };

// �v���C�V�[���Ŏg���t�H���g�̃n���h��
int g_PlaySceneFontHandle = 0;

void InitUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		uiText->active = false;
		uiText->posX = 0.0f;
		uiText->posY = 0.0f;
		memset(uiText->text, 0, sizeof(uiText->text));
	}
}

void LoadUIText()
{
	g_PlaySceneFontHandle = CreateFontToHandle("Nosutaru-dot M+H 10 Regular", 28, -1);
}

void StepUIText()
{
}

void UpdateUIText()
{
}

void DrawUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		if (!uiText->active) continue;

		// �`��
		DrawStringToHandle((int)uiText->posX, (int)uiText->posY, uiText->text, GetColor(255, 255, 255), g_PlaySceneFontHandle);
	}
}

void FinUIText()
{
}

// UIText�𐶐�
UITextData* CreateUIText(float posX, float posY, const char* text)
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		// ���g�p�g��T��
		if (!uiText->active)
		{
			// �A�N�e�B�u
			uiText->active = true;

			// ���W
			uiText->posX = posX;
			uiText->posY = posY;

			// �e�L�X�g
			strcpy_s(uiText->text, text);

			return uiText;
		}
	}

	// ��g���Ȃ�����
	return nullptr;
}

// �w�肵��UIText�ɕ������ݒ�
void SetUIText(UITextData* uiText, const char* text)
{
	strcpy_s(uiText->text, text);
}

// �\������UIText�𖢎g�p�ɂ���
void ResetUIText()
{
	UITextData* uiText = g_UITextData;
	for (int i = 0; i < UI_TEXT_MAX; i++, uiText++)
	{
		uiText->active = false;
	}
}
