#include "DxLib.h"
#include "sound.h"

int g_BGMHandle[BGM_TYPE_MAX] = { 0 };
int g_SEHandle[SE_TYPE_MAX] = { 0 };

// BGMロード
void LoadBGM()
{
	g_BGMHandle[BGM_TITLE] =
		LoadSoundMem("Data/SE/bgm/RPG_Battle_01");
	g_BGMHandle[BGM_PLAY] =
		LoadSoundMem("Data/SE/bgm/RPG_Battle_01");
	g_BGMHandle[BGM_GAME_OVER] = 
		LoadSoundMem("Data/Sound/BGM/GameOver.ogg");
	g_BGMHandle[BGM_GAME_CLEAR] =
		LoadSoundMem("Data/Sound/BGM/GameClear.ogg");
}

// BGM再生
void PlayBGM(BGMType type)
{
	PlaySoundMem(g_BGMHandle[type],
		DX_PLAYTYPE_LOOP);
}

// BGM停止
void StopBGM(BGMType type)
{
	StopSoundMem(g_BGMHandle[type]);
}

// BGM終了
void FinBGM()
{
	for (int i = 0; i < BGM_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_BGMHandle[i]);
	}
}


// SEロード
void LoadSE()
{
	g_SEHandle[SE_PLAYRE_SHOT] =
		LoadSoundMem("Data/SE/aaa/ショット");
	g_SEHandle[SE_PLAYER_DEAD] =
		LoadSoundMem("Data/SE/aaa/爆発2");
	g_SEHandle[SE_ENEMY_DEAD] =
		LoadSoundMem("Data/SE/aaa/爆発2");
	g_SEHandle[SE_BOSS_STAND] = 
		LoadSoundMem("Data/SE/aaa/ドラゴンの鳴き声1");
	g_SEHandle[SE_BOSS_DEAD] =
		LoadSoundMem("Data/SE/aaa/爆発2");
	g_SEHandle[SE_SLOT_STOP] =
		LoadSoundMem("");
	g_SEHandle[SE_SLOT_GET] =
		LoadSoundMem("Data/SE/bgm/free_sound7");
	g_SEHandle[SE_SLOT_BB] =
		LoadSoundMem("");
	g_SEHandle[SE_SLOT_RB] =
		LoadSoundMem("");
	g_SEHandle[SE_SLOT_CHANCE] =
		LoadSoundMem("Data/SE/aaa/効果音ジャグラー-ペカリ");

}


// SE再生
void PlaySE(SEType type)
{
	PlaySoundMem(g_SEHandle[type],
		DX_PLAYTYPE_BACK);
}

// SE終了
void FinSE()
{
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_SEHandle[i]);
	}
}
