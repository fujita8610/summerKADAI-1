#include "DxLib.h"
#include "SoundManager.h"

int g_BGMHandle[BGM_TYPE_MAX] = { 0 };
int g_SEHandle[SE_TYPE_MAX] = { 0 };

// BGM���[�h
void LoadBGM()
{
	g_BGMHandle[BGM_TITLE] = LoadSoundMem("Data/Sound/BGM/Title.ogg");
	g_BGMHandle[BGM_PLAY] = LoadSoundMem("Data/Sound/BGM/Play.ogg");
	g_BGMHandle[BGM_GAME_OVER] = LoadSoundMem("Data/Sound/BGM/GameOver.ogg");
	g_BGMHandle[BGM_GAME_CLEAR] = LoadSoundMem("Data/Sound/BGM/GameClear.ogg");
}

// BGM�Đ�
void PlayBGM(BGMType type)
{
	PlaySoundMem(g_BGMHandle[type], DX_PLAYTYPE_LOOP);
}

// BGM��~
void StopBGM(BGMType type)
{
	StopSoundMem(g_BGMHandle[type]);
}

// BGM�I��
void FinBGM()
{
	for (int i = 0; i < BGM_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_BGMHandle[i]);
	}
}


// SE���[�h
void LoadSE()
{
	g_SEHandle[SE_PLAYRE_SHOT] = LoadSoundMem("Data/Sound/SE/PlayerShot.ogg");
	g_SEHandle[SE_PLAYRE_SHOT_HIT] = LoadSoundMem("Data/Sound/SE/PlayerShotHit.ogg");
	g_SEHandle[SE_PLAYER_DEAD] = LoadSoundMem("Data/Sound/SE/PlayerDead.ogg");
	g_SEHandle[SE_ENEMY_DEAD] = LoadSoundMem("Data/Sound/SE/EnemyDead.ogg");
}

// SE�Đ�
void PlaySE(SEType type)
{
	PlaySoundMem(g_SEHandle[type], DX_PLAYTYPE_BACK);
}

// SE�I��
void FinSE()
{
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		DeleteSoundMem(g_SEHandle[i]);
	}
}
