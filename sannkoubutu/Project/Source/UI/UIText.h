#pragma once

#define UI_TEXT_LENGTH_MAX (256)

struct UITextData
{
	bool active;
	char text[UI_TEXT_LENGTH_MAX];
	float posX;
	float posY;
};

// �e���W�b�N���Ƃ̊֐�
void InitUIText();
void LoadUIText();
void StepUIText();
void UpdateUIText();
void DrawUIText();
void FinUIText();

// UIText�𐶐�
UITextData* CreateUIText(float posX, float posY, const char* text);

// �w�肵��UIText�ɕ������ݒ�
void SetUIText(UITextData* uiText, const char* text);

// �\������UIText�𖢎g�p�ɂ���
void ResetUIText();
