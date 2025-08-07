#include "DxLib.h"
#include "Collision.h"
#include "../Player/Player.h"
#include "../Enemy/EnemyParameter.h"
#include "../Enemy/Flies.h"
#include "../Enemy/DragonFly.h"
#include "../Enemy/Kapu.h"
#include "../Bullet/BulletParameter.h"
#include "../Bullet/StraightBullet.h"
#include <math.h>

// ��`�Ɠ_�̓����蔻��
// ����
// squarePosX:��`�̍���X���W
// squarePosY:��`�̍���Y���W
// squareWidth:��`�̉���
// squareHeight:��`�̍���
// pointX:�_��X���W
// pointY:�_��Y���W
// �߂�l
// �������Ă����true
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY)
{
	// �_��X���W����`�̊Ԃɂ��邩
	if (pointX >= squarePosX && pointX <= (squarePosX + squareWidth))
	{
		// �_��Y���W����`�̊Ԃɂ��邩
		if (pointY >= squarePosY && (pointY <= squarePosY + squareHeight))
		{
			// �������Ă���
			return true;
		}
	}

	return false;
}

// ��`�Ƌ�`�̓����蔻��
// ����
// squareA_PosX:��`A�̍���X���W
// squareA_PosY:��`A�̍���Y���W
// squareA_Width:��`A�̉���
// squareA_Height:��`A�̍���
// squareB_PosX:��`B�̍���X���W
// squareB_PosY:��`B�̍���Y���W
// squareB_Width:��`B�̉���
// squareB_Height:��`B�̍���
// �߂�l
// �������Ă����true
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height)
{
	// ��`A�̊e�ӂ̈ʒu���v�Z����
	float leftA = squareA_PosX;
	float rightA = squareA_PosX + squareA_Width;
	float topA = squareA_PosY;
	float bottomA = squareA_PosY + squareA_Height;

	// ��`B�̊e�ӂ̈ʒu���v�Z����
	float leftB = squareB_PosX;
	float rightB = squareB_PosX + squareB_Width;
	float topB = squareB_PosY;
	float bottomB = squareB_PosY + squareB_Height;

	// ���E�̕ӂ��߂荞��ł��邩�`�F�b�N
	if (rightA >= leftB && leftA <= rightB)
	{
		// �㉺�̕Ђ��߂荞��ł��邩�`�F�b�N
		if (bottomA >= topB && topA <= bottomB)
		{
			// �������Ă���
			return true;
		}
	}

	return false;
}

// �~�Ɠ_�̓����蔻��
// ����
// circlePosX:�~�̒��S���W�iX�j
// circlePosY:�~�̒��S���p�iY�j
// circleRadius:�~�̔��a
// pointX:�_��X���W
// pointY:�_��Y���W
// �߂�l
// �������Ă����true
bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY)
{
	// �~�̒��S����_�܂ł̋������v�Z����
	float distance = sqrtf((pointX - circlePosX) * (pointX - circlePosX) + (pointY - circlePosY) * (pointY - circlePosY));

	// ���߂����������a�̒����ȉ��ł���Γ������Ă���
	if (distance <= circleRadius)
	{
		return true;
	}

	return false;
}

// �~�Ɠ_�̓����蔻��
// ����
// circleA_PosX:�~A�̒��S���W�iX�j
// circleA_PosY:�~A�̒��S���p�iY�j
// circleA_Radius:�~A�̔��a
// circleB_PosX:�~B�̒��S���W�iX�j
// circleB_PosX:�~B�̒��S���p�iY�j
// circleB_Radius:�~B�̔��a
// �߂�l
// �������Ă����true
bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius)
{
	// �~�̒��S�Ԃ̋������v�Z����
	float distance = sqrtf((circleB_PosX - circleA_PosX) * (circleB_PosX - circleA_PosX) + (circleB_PosY - circleA_PosY) * (circleB_PosY - circleA_PosY));

	// ���S�Ԃ̋�����2�̉~�̔��a�̍��v�ȉ��ł���Γ������Ă���
	if (distance <= (circleA_Radius + circleB_Radius))
	{
		return true;
	}

	return false;
}

void CheckPlayerFlies()
{
	// �v���C���[��Flies�̓����蔻��
	PlayerData* player = GetPlayer();
	EnemyFliesData* flies = GetFlies();

	// �v���C���[�������Ă��Ė��G�łȂ����������肷��
	if (player->active && !player->invisible)
	{
		// �v���C���[�̒��S���W
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
		{
			// ����ł����画�肵�Ȃ�
			if (!flies->active) continue;

			// Flies�̒��S���W
			float fliesCenterX = flies->posX + ENEMY_FLIES_WIDTH / 2;
			float fliesCenterY = flies->posY + ENEMY_FLIES_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(playerCenterX, playerCenterY, PLAYER_RADIUS,
				fliesCenterX, fliesCenterY, ENEMY_FLIES_RADIUS))
			{
				PlayerHitEnemy();
				FliesHitPlayer(i);
			}
		}
	}
}

void CheckPlayerDragonFly()
{
	// �v���C���[��Flies�̓����蔻��
	PlayerData* player = GetPlayer();
	EnemyDragonFlyData* dragonFly = GetDragonFly();

	// �v���C���[�������Ă��Ė��G�łȂ����������肷��
	if (player->active && !player->invisible)
	{
		// �v���C���[�̒��S���W
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
		{
			// ����ł����画�肵�Ȃ�
			if (!dragonFly->active) continue;

			// DragonFly�̒��S���W
			float dragonFlyCenterX = dragonFly->posX + ENEMY_DRAGON_FLY_WIDTH / 2;
			float dragonFlyCenterY = dragonFly->posY + ENEMY_DRAGON_FLY_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(playerCenterX, playerCenterY, PLAYER_RADIUS,
				dragonFlyCenterX, dragonFlyCenterY, ENEMY_DRAGON_FLY_RADIUS))
			{
				PlayerHitEnemy();
				DragonFlyHitPlayer(i);
			}
		}
	}
}

void CheckPlayerKapu()
{
	// �v���C���[��Flies�̓����蔻��
	PlayerData* player = GetPlayer();
	EnemyKapuData* kapu = GetKapu();

	// �v���C���[�������Ă��Ė��G�łȂ����������肷��
	if (player->active && !player->invisible)
	{
		// �v���C���[�̒��S���W
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
		{
			// ����ł����画�肵�Ȃ�
			if (!kapu->active) continue;

			// DragonFly�̒��S���W
			float kapuCenterX = kapu->posX + ENEMY_KAPU_WIDTH / 2;
			float kapuCenterY = kapu->posY + ENEMY_KAPU_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(playerCenterX, playerCenterY, PLAYER_RADIUS,
				kapuCenterX, kapuCenterY, ENEMY_KAPU_RADIUS))
			{
				PlayerHitEnemy();
				KapuHitPlayer(i);
			}
		}
	}

}

void CheckPlayerBulletFlies()
{
	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// ���g�p�o���b�g�͔��肵�Ȃ�
		if (!bullet->active)continue;

		// �G�l�~�[���������e�Ƃ͔��肵�Ȃ�
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// �e�̒��S���W
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyFliesData* flies = GetFlies();
		for (int j = 0; j < ENEMY_FLIES_MAX; j++, flies++)
		{
			// ���g�p�G�l�~�[�͔��肵�Ȃ�
			if (!flies->active)continue;

			// Flies�̒��S���W
			float fliesCenterX = flies->posX + ENEMY_FLIES_WIDTH / 2;
			float fliesCenterY = flies->posY + ENEMY_FLIES_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(bulletCenterX, bulletCenterY, bullet->radius,
				fliesCenterX, fliesCenterY, ENEMY_FLIES_RADIUS))
			{
				StraightBulletHitEnemy(i);
				FliesHitPlayerBullet(j);
			}
		}
	}
}

void CheckPlayerBulletDragonFly()
{
	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// ���g�p�o���b�g�͔��肵�Ȃ�
		if (!bullet->active)continue;

		// �G�l�~�[���������e�Ƃ͔��肵�Ȃ�
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// �e�̒��S���W
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyDragonFlyData* dragonFly = GetDragonFly();
		for (int j = 0; j < ENEMY_DRAGON_FLY_MAX; j++, dragonFly++)
		{
			// ���g�p�G�l�~�[�͔��肵�Ȃ�
			if (!dragonFly->active)continue;

			// DragonFly�̒��S���W
			float dragonFlyCenterX = dragonFly->posX + ENEMY_DRAGON_FLY_WIDTH / 2;
			float dragonFlyCenterY = dragonFly->posY + ENEMY_DRAGON_FLY_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(bulletCenterX, bulletCenterY, bullet->radius,
				dragonFlyCenterX, dragonFlyCenterY, ENEMY_DRAGON_FLY_RADIUS))
			{
				StraightBulletHitEnemy(i);
				DragonFlyHitPlayerBullet(j);
			}
		}
	}
}

void CheckPlayerBulletKapu()
{
	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// ���g�p�o���b�g�͔��肵�Ȃ�
		if (!bullet->active)continue;

		// �G�l�~�[���������e�Ƃ͔��肵�Ȃ�
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// �e�̒��S���W
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyKapuData* kapu = GetKapu();
		for (int j = 0; j < ENEMY_KAPU_MAX; j++, kapu++)
		{
			// ���g�p�G�l�~�[�͔��肵�Ȃ�
			if (!kapu->active)continue;

			// DragonFly�̒��S���W
			float kapuCenterX = kapu->posX + ENEMY_KAPU_WIDTH / 2;
			float kapuCenterY = kapu->posY + ENEMY_KAPU_HEIGHT / 2;

			// �~�œ����蔻����Ƃ�
			if (CheckCircleCircle(bulletCenterX, bulletCenterY, bullet->radius,
				kapuCenterX, kapuCenterY, ENEMY_KAPU_RADIUS))
			{
				StraightBulletHitEnemy(i);
				KapuHitPlayerBullet(j);
			}
		}
	}
}

void CheckEnemyBulletPlayer()
{
	PlayerData* player = GetPlayer();

	// �v���C���[�����S���Ă����薳�G�ł���Δ��肵�Ȃ�
	if (!player->active || player->invisible)return;


	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// ���g�p�o���b�g�͔��肵�Ȃ�
		if (!bullet->active)continue;

		// �v���C���[���������e�Ƃ͔��肵�Ȃ�
		if (bullet->tag == BULLET_COLLISION_TAG_PLAYER)continue;

		// �e�̒��S���W
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		// DragonFly�̒��S���W
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		// �~�œ����蔻����Ƃ�
		if (CheckCircleCircle(bulletCenterX, bulletCenterY, bullet->radius,
			playerCenterX, playerCenterY, PLAYER_RADIUS))
		{
			StraightBulletHitPlayer(i);
			PlayerHitEnemyBullet();
		}
	}
}

void CheckCollision()
{
	// �����ɓ����蔻��̏���������

	// Player��Flies�̓����蔻��
	CheckPlayerFlies();

	// Player��DragonFly�̓����蔻��
	CheckPlayerDragonFly();

	// Player��Kapu�̓����蔻��
	CheckPlayerKapu();

	// �v���C���[�̒e��Flies�̓����蔻��
	CheckPlayerBulletFlies();

	// �v���C���[�̒e��DragonFly�̓����蔻��
	CheckPlayerBulletDragonFly();

	// �v���C���[�̒e��Kapu�̓����蔻��
	CheckPlayerBulletKapu();

	// �G�l�~�[�̒e�ƃv���C���[�̓����蔻��
	CheckEnemyBulletPlayer();
}

