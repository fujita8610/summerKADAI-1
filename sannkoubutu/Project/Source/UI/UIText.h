#pragma once

#define UI_TEXT_LENGTH_MAX (256)

struct UITextData
{
	bool active;
	char text[UI_TEXT_LENGTH_MAX];
	float posX;
	float posY;
};

// 各ロジックごとの関数
void InitUIText();
void LoadUIText();
void StepUIText();
void UpdateUIText();
void DrawUIText();
void FinUIText();

// UITextを生成
UITextData* CreateUIText(float posX, float posY, const char* text);

// 指定したUITextに文字列を設定
void SetUIText(UITextData* uiText, const char* text);

// 表示中のUITextを未使用にする
void ResetUIText();
