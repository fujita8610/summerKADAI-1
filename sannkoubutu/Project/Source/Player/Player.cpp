#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Collision/Collision.h"
#include "../Score/Score.h"
#include "../Effect/AnimationEffect.h"
#include "../Bullet/BulletManager.h"
#include "../Scene/SceneManager.h"
#include "../Sound/SoundManager.h"

// �c�@�\���̕�����
#define PLAYER_LIFE_STRING ("x%02d")

// �v���C���[�ݒ�֘A
#define PLAYER_DEFAULT_POS_X (200.0f)
#define PLAYER_DEFAULT_POS_Y (250.0f)
#define PLAYER_MOVE_SPEED (3.0f)

// �e�֘A
#define PLAYER_NORMAL_SHOT_SPEED	(32.0f)
#define PLAYER_NORMAL_SHOT_LIFE		(600)
#define PLAYER_NORMAL_SHOT_OFFSET_X	(50.0f)
#define PLAYER_NORMAL_SHOT_OFFSET_Y	(10.0f)
#define PLAYER_NORMAL_SHOT_INTERVAL (15)

// �ړ��\�G���A
#define PLAYER_MOVE_AREA_LEFT (0.0f)
#define PLAYER_MOVE_AREA_RIGHT (1536.0f)
#define PLAYER_MOVE_AREA_TOP (0.0f)
#define PLAYER_MOVE_AREA_BOTTOM (743.0f)

// �v���C���[�̎c�@
#define PLAYER_DEFAULT_LIFE (2)

// ���X�|�[���܂ł̑ҋ@����
#define PLAYER_RESPAWN_WAIT (180)

// ���X�|�[�����̖��G����
#define PLAYER_RESPAWN_INVISIBLE_TIME (180)

// �v���C���[���S�G�t�F�N�g�C���^�[�o��
#define PLAYER_DEAD_EFFECT_INTERVAL (2)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.life = 0;
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.bulletIntervalTimer = 0;
	g_PlayerData.respawnTimer = 0;
	g_PlayerData.active = false;
	g_PlayerData.invisible = false;
	g_PlayerData.lifeText = nullptr;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/Player.png");
}

void StartPlayer()
{
	// �����t���O�𗧂Ă�
	g_PlayerData.active = true;

	// �c�@�̏����l�ݒ�
	g_PlayerData.life = PLAYER_DEFAULT_LIFE;

	// �c�@��UI����
	char text[256];
	sprintf_s(text, PLAYER_LIFE_STRING, g_PlayerData.life);
	g_PlayerData.lifeText = CreateUIText(60.0f, 795.0f, text);
}

void StepPlayer()
{
	// ����ł������p����
	if (!g_PlayerData.active)
	{
		// �ҋ@���Ԃ��߂����烊�X�|�[��
		if (g_PlayerData.respawnTimer <= 0)
		{
			bool isSuccessRespawn = RespawnPlayer();
			// ���X�|�[���ł��Ȃ�������Q�[���I�[�o�[
			if (!isSuccessRespawn)
			{
				ChangeScene(SCENE_GAME_OVER);
			}
		}
		g_PlayerData.respawnTimer--;

		return;
	}

	// �ړ��ʂ͖��񃊃Z�b�g����
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;

	// �ʏ�e�̃C���^�[�o�����Ԃ����炷
	if (g_PlayerData.bulletIntervalTimer > 0)
	{
		g_PlayerData.bulletIntervalTimer--;
	}

	// �����
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.moveY = -PLAYER_MOVE_SPEED;
	}
	// ������
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	}
	// ������
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// �E����
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	}

	// Z����
	if (IsInputKey(KEY_Z))
	{
		// �C���^�[�o�����Ԃ������Ă��猂��
		if (g_PlayerData.bulletIntervalTimer <= 0)
		{
			// �e���ˏ���ݒ�
			const FireBulletData FIRE_DATA =
			{
				PLAYER_NORMAL_SHOT_LIFE,
				g_PlayerData.posX + PLAYER_NORMAL_SHOT_OFFSET_X,
				g_PlayerData.posY + PLAYER_NORMAL_SHOT_OFFSET_Y,
				PLAYER_NORMAL_SHOT_SPEED,
				0.0f,
			};
			FireBullet(BULLET_CATEGORY_STRAIGHT, STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, FIRE_DATA, BULLET_COLLISION_TAG_PLAYER);

			// ���ˉ��Đ�
			PlaySE(SE_PLAYRE_SHOT);

			// �C���^�[�o���ݒ�
			g_PlayerData.bulletIntervalTimer = PLAYER_NORMAL_SHOT_INTERVAL;
		}
	}

	// ���G���̏���
	if (g_PlayerData.invisible)
	{
		g_PlayerData.invisibleTimer--;
	}
}

void UpdatePlayer()
{
	// ����ł����珈�����Ȃ�
	if (!g_PlayerData.active) return;

	// �ړ�����
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

	// ��ʊO�ɏo�Ȃ��悤�Ɉړ�����
	if (g_PlayerData.posX < PLAYER_MOVE_AREA_LEFT) g_PlayerData.posX = PLAYER_MOVE_AREA_LEFT;
	if (g_PlayerData.posX > PLAYER_MOVE_AREA_RIGHT) g_PlayerData.posX = PLAYER_MOVE_AREA_RIGHT;
	if (g_PlayerData.posY < PLAYER_MOVE_AREA_TOP) g_PlayerData.posY = PLAYER_MOVE_AREA_TOP;
	if (g_PlayerData.posY > PLAYER_MOVE_AREA_BOTTOM) g_PlayerData.posY = PLAYER_MOVE_AREA_BOTTOM;

	// ���G�����`�F�b�N
	if (g_PlayerData.invisible && g_PlayerData.invisibleTimer <= 0)
	{
		g_PlayerData.invisible = false;
	}
}

void DrawPlayer()
{
	// ����ł����珈�����Ȃ�
	if (!g_PlayerData.active) return;

	// ���G�̎��͓_�ł���
	if (g_PlayerData.invisible)
	{
		// 3�t���[����1�x�����`�悵�ē_�ł�����
		if (g_PlayerData.invisibleTimer % 3 == 0)
		{
			DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
		}
	}
	else
	{
		// �ʏ�`��
		DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);
	}
}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}

// ���X�|�[������(���X�|�[���ł��Ȃ�������false��Ԃ�)
bool RespawnPlayer()
{
	// �c�@�`�F�b�N
	if (g_PlayerData.life > 0)
	{
		// �A�N�e�B�u
		g_PlayerData.active = true;

		// ���G���
		g_PlayerData.invisible = true;
		g_PlayerData.invisibleTimer = PLAYER_RESPAWN_INVISIBLE_TIME;

		// �����ʒu�ɔz�u
		g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
		g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;

		// �c�@�����炷
		g_PlayerData.life--;

		// �c�@UI�X�V
		char text[256];
		sprintf_s(text, PLAYER_LIFE_STRING, g_PlayerData.life);
		SetUIText(g_PlayerData.lifeText, text);

		// ���X�|�[������
		return true;
	}

	// ���X�|�[���s��
	return false;
}

void PlayerDead()
{
	// ���S
	g_PlayerData.active = false;

	// ���X�|�[���ҋ@�J�n
	g_PlayerData.respawnTimer = PLAYER_RESPAWN_WAIT;

	// ���S�G�t�F�N�g
	StartAnimationEffect(PLAYER_DEAD, g_PlayerData.posX, g_PlayerData.posY, PLAYER_DEAD_EFFECT_INTERVAL);

	// ���SSE
	PlaySE(SE_PLAYER_DEAD);
}

// �G�ƏՓ˂���
void PlayerHitEnemy()
{
	// �Փ˂����玀�S
	PlayerDead();
}

// �G�̒e�ƏՓ˂���
void PlayerHitEnemyBullet()
{
	// �Փ˂����玀�S
	PlayerDead();
}
