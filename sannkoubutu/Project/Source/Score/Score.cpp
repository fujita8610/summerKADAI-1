#include "Score.h"
#include "../UI/UIText.h"
#include <stdio.h>

#define SCORE_STRING ("SCORE %08d")
#define HI_SCORE_STRING ("HI-SCORE %08d")

// ���݂̃X�R�A
int g_Score = 0;

// �X�V�O�̃X�R�A
int g_PrevScore = 0;

// �n�C�X�R�A
int g_HiScore = 0;

// �\��UI
UITextData* g_UIScore = nullptr;
UITextData* g_UIHiScore = nullptr;

// �X�R�A������
void InitScore()
{
	// �l������
	g_Score = 0;
	g_UIScore = nullptr;
	g_UIHiScore = nullptr;
}

// �X�R�A�X�V
// �����蔻�菈�����G��|�������ǂ������肷��̂ŁA
// �K�������蔻�������ŌĂ΂��悤�ɂ���
void UpdateScore()
{
	// �X�R�A���������������UI�Ή�����
	if (g_Score != g_PrevScore)
	{
		char text[256];

		// �n�C�X�R�A���X�V������
		if (g_Score > g_HiScore)
		{
			// �X�V
			g_HiScore = g_Score;

			// UI���X�V
			sprintf_s(text, HI_SCORE_STRING, g_HiScore);
			SetUIText(g_UIHiScore, text);
		}

		// �X�R�AUI�X�V
		sprintf_s(text, SCORE_STRING, g_Score);
		SetUIText(g_UIScore, text);
	}
}

// �X�R�A�\��UI����
void CreateScoreUI(float posX, float posY)
{
	char text[256];
	sprintf_s(text, SCORE_STRING, g_Score);
	g_UIScore = CreateUIText(posX, posY, text);
}

void CreateHiScoreUI(float posX, float posY)
{
	char text[256];
	sprintf_s(text, HI_SCORE_STRING, g_HiScore);
	g_UIHiScore = CreateUIText(posX, posY, text);
}

// �X�R�A�ݒ�
void SetScore(int score)
{
	g_Score = score;
}

// �X�R�A�擾
int GetScore()
{
	return g_Score;
}

// �n�C�X�R�A�ݒ�
void SetHiScore(int hiScore)
{
	g_HiScore = hiScore;
}

// �n�C�X�R�A�擾
int GetHiScore()
{
	return g_HiScore;
}
