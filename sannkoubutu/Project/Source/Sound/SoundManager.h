#pragma once

// BGM関連 ////////////////////////

// BGMタイプ
enum BGMType
{
	BGM_TITLE,
	BGM_PLAY,
	BGM_GAME_OVER,
	BGM_GAME_CLEAR,
	BGM_TYPE_MAX
};

// BGMロード
void LoadBGM();
// BGM再生
void PlayBGM(BGMType type);
// BGM停止
void StopBGM(BGMType type);
// BGM終了
void FinBGM();

////////////////////////////////////

// SE関連 ////////////////////////

enum SEType
{
	SE_PLAYRE_SHOT,
	SE_PLAYRE_SHOT_HIT,
	SE_PLAYER_DEAD,
	SE_ENEMY_DEAD,
	SE_TYPE_MAX
};

// SEロード
void LoadSE();
// SE再生
void PlaySE(SEType type);
// SE終了
void FinSE();

////////////////////////////////////
