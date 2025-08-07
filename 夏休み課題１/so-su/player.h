#pragma once

// �v���C���[�T�C�Y
#define PLAYER_WIDTH	(64.0f)
#define PLAYER_HEIGHT	(64.0f)
#define PLAYER_RADIUS	(32.0f)

// �v���C���[�f�[�^
struct PlayerData
{
	bool active;				// �����t���O
	bool invisible;				// ���G�t���O
	int handle;					// �摜�n���h��
	int bulletIntervalTimer;	// �e�̔��ˊԊu�^�C�}�[
	int respawnTimer;			// ���X�|�[���ҋ@�^�C�}�[
	int invisibleTimer;			// ���G���ԃ^�C�}�[
	int life;					// �c�@��
	float posX;					// X���W
	float posY;					// Y���W
	float moveX;				// X�ړ���
	float moveY;				// Y�ړ���
	
};


// �֐��̃v���g�^�C�v�錾
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// �擾�֐�
PlayerData* GetPlayer();

// ���X�|�[������(���X�|�[���ł��Ȃ�������false��Ԃ�)
bool RespawnPlayer();

// �����蔻��
void PlayerHitEnemy();
void PlayerHitEnemyBullet();
