#include "Score.h"
#include "../UI/UIText.h"
#include <stdio.h>

#define SCORE_STRING ("SCORE %08d")
#define HI_SCORE_STRING ("HI-SCORE %08d")

// 現在のスコア
int g_Score = 0;

// 更新前のスコア
int g_PrevScore = 0;

// ハイスコア
int g_HiScore = 0;

// 表示UI
UITextData* g_UIScore = nullptr;
UITextData* g_UIHiScore = nullptr;

// スコア初期化
void InitScore()
{
	// 値初期化
	g_Score = 0;
	g_UIScore = nullptr;
	g_UIHiScore = nullptr;
}

// スコア更新
// 当たり判定処理が敵を倒したかどうか判定するので、
// 必ず当たり判定よりも後で呼ばれるようにする
void UpdateScore()
{
	// スコアが書き換わったらUI対応する
	if (g_Score != g_PrevScore)
	{
		char text[256];

		// ハイスコアを更新したか
		if (g_Score > g_HiScore)
		{
			// 更新
			g_HiScore = g_Score;

			// UIも更新
			sprintf_s(text, HI_SCORE_STRING, g_HiScore);
			SetUIText(g_UIHiScore, text);
		}

		// スコアUI更新
		sprintf_s(text, SCORE_STRING, g_Score);
		SetUIText(g_UIScore, text);
	}
}

// スコア表示UI生成
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

// スコア設定
void SetScore(int score)
{
	g_Score = score;
}

// スコア取得
int GetScore()
{
	return g_Score;
}

// ハイスコア設定
void SetHiScore(int hiScore)
{
	g_HiScore = hiScore;
}

// ハイスコア取得
int GetHiScore()
{
	return g_HiScore;
}
