#include "DxLib.h"
#include "../../Player/Player.h"
#include "../../BackGround/BackGround.h"
#include "../../Scene/SceneManager.h"
#include "../../Bullet/BulletManager.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Sound/SoundManager.h"
#include "../../Collision/Collision.h"
#include "../../Effect/AnimationEffect.h"
#include "../../UI/UIImage.h"
#include "../../UI/UIText.h"
#include "../../Score/Score.h"

// �w�i�̃X�s�[�h
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// �w�i������
	InitBackGround();

	// �v���C���[������
	InitPlayer();

	// �G�l�~�[������
	InitEnemy();

	// �e��������
	InitBullet();

	// �G�t�F�N�g��������
	InitAnimationEffect();

	// �X�R�A������
	InitScore();
}

void LoadPlayScene()
{
	// �w�i���[�h
	LoadBackGround("Data/Title/TitleBG.png", BACK_GROUND_LAYER_1);
	// �w�i�X�N���[��
	SetBackGroundMove(BACK_GROUND_SPEED, 0.0f, BACK_GROUND_LAYER_1);

	// �v���C���[���[�h
	LoadPlayer();

	// �G�l�~�[���[�h
	LoadEnemy();

	// �e���[�h
	LoadBullet();

	// �G�t�F�N�g���[�h
	LoadAnimationEffect();
}

void StartPlayScene()
{
	// �v���C���[�J�n
	StartPlayer();

	// �eUI����
	CreateUIImage(UI_IMAGE_PLAY_FOOTER_FRAME, 0.0f, 775.0f);// �t�b�^�[�g
	CreateUIImage(UI_IMAGE_HEART, 24.0f, 800.0f);			// �c�@�n�[�g
	CreateUIText(990.0f, 840.0f, "TARGET");					// �^�[�Q�b�g����
	CreateUIImage(UI_IMAGE_TARGET_KAPU, 1140.0f, 800.0f);	// �^�[�Q�b�g�G�l�~�[�摜
	// �X�R�A
	CreateScoreUI(30.0f, 840.0f);
	// �n�C�X�R�A
	CreateHiScoreUI(550.0f, 840.0f);

	// BGM�Đ�
	PlayBGM(BGM_PLAY);

}

void StepPlayScene()
{
	// �w�i�X�e�b�v
	StepBackGround();

	// �v���C���[�X�e�b�v
	StepPlayer();

	// �G�l�~�[�X�e�b�v
	StepEnemy();

	// �e�X�e�b�v
	StepBullet();

	// �G�l�~�[�o���V�X�e�����X�e�b�v
	StepEnemySpawnSystem();

	// �G�t�F�N�g���X�e�b�v
	StepAnimationEffect();

	// UI�X�e�b�v
	StepUIImage();
	StepUIText();
}

void UpdatePlayScene()
{
	// �w�i�X�V
	UpdateBackGround();

	// �v���C���[�X�V
	UpdatePlayer();

	// �G�l�~�[�X�V
	UpdateEnemy();

	// �e�X�V
	UpdateBullet();

	// �G�t�F�N�g�X�V
	UpdateAnimationEffect();

	// UI�X�V
	UpdateUIImage();
	UpdateUIText();
	
	// �����蔻��
	CheckCollision();

	// �X�R�A�X�V
	UpdateScore();

	// Kapu���Q�̌��j������N���A�V�[����
	if (GetEnemyDestroyNum(ENEMY_TYPE_KAPU) >= 2)
	{
		ChangeScene(SCENE_GAME_CLEAR);
	}
}

void DrawPlayScene()
{
	// �w�i�`��
	DrawBackGround();

	// �e�`��
	DrawBullet();

	// �G�l�~�[�`��
	DrawEnemy();

	// �v���C���[�`��
	DrawPlayer();

	// �G�t�F�N�g�`��
	DrawAnimationEffect();

	// UI�`��
	DrawUIImage();
	DrawUIText();
}

void FinPlayScene()
{
	// �w�i�I��
	FinBackGround();

	// �v���C���[�I��
	FinPlayer();

	// �G�l�~�[�I��
	FinEnemy();

	// �e�I��
	FinBullet();

	// �G�t�F�N�g�I��
	FinAnimationEffect();

	// UI���Z�b�g
	ResetUIImage();
	ResetUIText();

	// BGM��~
	StopBGM(BGM_PLAY);
}
