#pragma once

// UIImage�̎��
enum UIImageType
{
	// Play�V�[���Ŏg��
	UI_IMAGE_PLAY_FOOTER_FRAME,
	UI_IMAGE_HEART,
	UI_IMAGE_TARGET_KAPU,

	// ��ލő吔
	UI_IMAGE_TYPE_MAX,
};

// UIImage�̃f�[�^
struct UIImageData
{
	bool active;
	int handle;
	float posX;
	float posY;
};

// �e���W�b�N���Ƃ̊֐�
void InitUIImage();
void LoadUIImage();
void StepUIImage();
void UpdateUIImage();
void DrawUIImage();
void FinUIImage();

// UIImage�𐶐�����
void CreateUIImage(UIImageType type, float posX, float posY);

// �\������UIImage�𖢎g�p�ɂ���
// �V�[���̐؂�ւ����ȂǂŎg��
void ResetUIImage();
