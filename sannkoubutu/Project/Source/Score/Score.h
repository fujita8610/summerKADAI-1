#pragma once

// �X�R�A������
void InitScore();
void UpdateScore();

// �X�R�A�\��UI����
void CreateScoreUI(float posX, float posY);
void CreateHiScoreUI(float posX, float posY);

// �X�R�A�ݒ�
void SetScore(int score);

// �X�R�A�擾
int GetScore();

// �n�C�X�R�A�ݒ�
void SetHiScore(int hiScore);

// �n�C�X�R�A�擾
int GetHiScore();
