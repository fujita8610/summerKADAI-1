#pragma once

// スコア初期化
void InitScore();
void UpdateScore();

// スコア表示UI生成
void CreateScoreUI(float posX, float posY);
void CreateHiScoreUI(float posX, float posY);

// スコア設定
void SetScore(int score);

// スコア取得
int GetScore();

// ハイスコア設定
void SetHiScore(int hiScore);

// ハイスコア取得
int GetHiScore();
