#pragma once

// BGM�֘A ////////////////////////

// BGM�^�C�v
enum BGMType
{
	BGM_TITLE,
	BGM_PLAY,
	BGM_GAME_OVER,
	BGM_GAME_CLEAR,
	BGM_TYPE_MAX
};

// BGM���[�h
void LoadBGM();
// BGM�Đ�
void PlayBGM(BGMType type);
// BGM��~
void StopBGM(BGMType type);
// BGM�I��
void FinBGM();

////////////////////////////////////

// SE�֘A ////////////////////////

enum SEType
{
	SE_PLAYRE_SHOT,
	SE_PLAYRE_SHOT_HIT,
	SE_PLAYER_DEAD,
	SE_ENEMY_DEAD,
	SE_TYPE_MAX
};

// SE���[�h
void LoadSE();
// SE�Đ�
void PlaySE(SEType type);
// SE�I��
void FinSE();

////////////////////////////////////
