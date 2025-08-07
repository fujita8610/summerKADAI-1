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

// 矩形と点の当たり判定
// 引数
// squarePosX:矩形の左上X座標
// squarePosY:矩形の左上Y座標
// squareWidth:矩形の横幅
// squareHeight:矩形の高さ
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY)
{
	// 点のX座標が矩形の間にあるか
	if (pointX >= squarePosX && pointX <= (squarePosX + squareWidth))
	{
		// 点のY座標が矩形の間にあるか
		if (pointY >= squarePosY && (pointY <= squarePosY + squareHeight))
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 矩形と矩形の当たり判定
// 引数
// squareA_PosX:矩形Aの左上X座標
// squareA_PosY:矩形Aの左上Y座標
// squareA_Width:矩形Aの横幅
// squareA_Height:矩形Aの高さ
// squareB_PosX:矩形Bの左上X座標
// squareB_PosY:矩形Bの左上Y座標
// squareB_Width:矩形Bの横幅
// squareB_Height:矩形Bの高さ
// 戻り値
// 当たっていればtrue
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height)
{
	// 矩形Aの各辺の位置を計算する
	float leftA = squareA_PosX;
	float rightA = squareA_PosX + squareA_Width;
	float topA = squareA_PosY;
	float bottomA = squareA_PosY + squareA_Height;

	// 矩形Bの各辺の位置を計算する
	float leftB = squareB_PosX;
	float rightB = squareB_PosX + squareB_Width;
	float topB = squareB_PosY;
	float bottomB = squareB_PosY + squareB_Height;

	// 左右の辺がめり込んでいるかチェック
	if (rightA >= leftB && leftA <= rightB)
	{
		// 上下の片がめり込んでいるかチェック
		if (bottomA >= topB && topA <= bottomB)
		{
			// 当たっている
			return true;
		}
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circlePosX:円の中心座標（X）
// circlePosY:円の中心座用（Y）
// circleRadius:円の半径
// pointX:点のX座標
// pointY:点のY座標
// 戻り値
// 当たっていればtrue
bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY)
{
	// 円の中心から点までの距離を計算する
	float distance = sqrtf((pointX - circlePosX) * (pointX - circlePosX) + (pointY - circlePosY) * (pointY - circlePosY));

	// 求めた距離が半径の長さ以下であれば当たっている
	if (distance <= circleRadius)
	{
		return true;
	}

	return false;
}

// 円と点の当たり判定
// 引数
// circleA_PosX:円Aの中心座標（X）
// circleA_PosY:円Aの中心座用（Y）
// circleA_Radius:円Aの半径
// circleB_PosX:円Bの中心座標（X）
// circleB_PosX:円Bの中心座用（Y）
// circleB_Radius:円Bの半径
// 戻り値
// 当たっていればtrue
bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius)
{
	// 円の中心間の距離を計算する
	float distance = sqrtf((circleB_PosX - circleA_PosX) * (circleB_PosX - circleA_PosX) + (circleB_PosY - circleA_PosY) * (circleB_PosY - circleA_PosY));

	// 中心間の距離が2つの円の半径の合計以下であれば当たっている
	if (distance <= (circleA_Radius + circleB_Radius))
	{
		return true;
	}

	return false;
}

void CheckPlayerFlies()
{
	// プレイヤーとFliesの当たり判定
	PlayerData* player = GetPlayer();
	EnemyFliesData* flies = GetFlies();

	// プレイヤーが生きていて無敵でない時だけ判定する
	if (player->active && !player->invisible)
	{
		// プレイヤーの中心座標
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_FLIES_MAX; i++, flies++)
		{
			// 死んでいたら判定しない
			if (!flies->active) continue;

			// Fliesの中心座標
			float fliesCenterX = flies->posX + ENEMY_FLIES_WIDTH / 2;
			float fliesCenterY = flies->posY + ENEMY_FLIES_HEIGHT / 2;

			// 円で当たり判定をとる
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
	// プレイヤーとFliesの当たり判定
	PlayerData* player = GetPlayer();
	EnemyDragonFlyData* dragonFly = GetDragonFly();

	// プレイヤーが生きていて無敵でない時だけ判定する
	if (player->active && !player->invisible)
	{
		// プレイヤーの中心座標
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_DRAGON_FLY_MAX; i++, dragonFly++)
		{
			// 死んでいたら判定しない
			if (!dragonFly->active) continue;

			// DragonFlyの中心座標
			float dragonFlyCenterX = dragonFly->posX + ENEMY_DRAGON_FLY_WIDTH / 2;
			float dragonFlyCenterY = dragonFly->posY + ENEMY_DRAGON_FLY_HEIGHT / 2;

			// 円で当たり判定をとる
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
	// プレイヤーとFliesの当たり判定
	PlayerData* player = GetPlayer();
	EnemyKapuData* kapu = GetKapu();

	// プレイヤーが生きていて無敵でない時だけ判定する
	if (player->active && !player->invisible)
	{
		// プレイヤーの中心座標
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		for (int i = 0; i < ENEMY_KAPU_MAX; i++, kapu++)
		{
			// 死んでいたら判定しない
			if (!kapu->active) continue;

			// DragonFlyの中心座標
			float kapuCenterX = kapu->posX + ENEMY_KAPU_WIDTH / 2;
			float kapuCenterY = kapu->posY + ENEMY_KAPU_HEIGHT / 2;

			// 円で当たり判定をとる
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
		// 未使用バレットは判定しない
		if (!bullet->active)continue;

		// エネミーが撃った弾とは判定しない
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// 弾の中心座標
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyFliesData* flies = GetFlies();
		for (int j = 0; j < ENEMY_FLIES_MAX; j++, flies++)
		{
			// 未使用エネミーは判定しない
			if (!flies->active)continue;

			// Fliesの中心座標
			float fliesCenterX = flies->posX + ENEMY_FLIES_WIDTH / 2;
			float fliesCenterY = flies->posY + ENEMY_FLIES_HEIGHT / 2;

			// 円で当たり判定をとる
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
		// 未使用バレットは判定しない
		if (!bullet->active)continue;

		// エネミーが撃った弾とは判定しない
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// 弾の中心座標
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyDragonFlyData* dragonFly = GetDragonFly();
		for (int j = 0; j < ENEMY_DRAGON_FLY_MAX; j++, dragonFly++)
		{
			// 未使用エネミーは判定しない
			if (!dragonFly->active)continue;

			// DragonFlyの中心座標
			float dragonFlyCenterX = dragonFly->posX + ENEMY_DRAGON_FLY_WIDTH / 2;
			float dragonFlyCenterY = dragonFly->posY + ENEMY_DRAGON_FLY_HEIGHT / 2;

			// 円で当たり判定をとる
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
		// 未使用バレットは判定しない
		if (!bullet->active)continue;

		// エネミーが撃った弾とは判定しない
		if (bullet->tag == BULLET_COLLISION_TAG_ENEMY)continue;

		// 弾の中心座標
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		EnemyKapuData* kapu = GetKapu();
		for (int j = 0; j < ENEMY_KAPU_MAX; j++, kapu++)
		{
			// 未使用エネミーは判定しない
			if (!kapu->active)continue;

			// DragonFlyの中心座標
			float kapuCenterX = kapu->posX + ENEMY_KAPU_WIDTH / 2;
			float kapuCenterY = kapu->posY + ENEMY_KAPU_HEIGHT / 2;

			// 円で当たり判定をとる
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

	// プレイヤーが死亡していたり無敵であれば判定しない
	if (!player->active || player->invisible)return;


	StraightBulletData* bullet = GetStraightBullet();
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 未使用バレットは判定しない
		if (!bullet->active)continue;

		// プレイヤーが撃った弾とは判定しない
		if (bullet->tag == BULLET_COLLISION_TAG_PLAYER)continue;

		// 弾の中心座標
		float bulletCenterX = bullet->posX + bullet->width / 2;
		float bulletCenterY = bullet->posY + bullet->height / 2;

		// DragonFlyの中心座標
		float playerCenterX = player->posX + PLAYER_WIDTH / 2;
		float playerCenterY = player->posY + PLAYER_HEIGHT / 2;

		// 円で当たり判定をとる
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
	// ここに当たり判定の処理を書く

	// PlayerとFliesの当たり判定
	CheckPlayerFlies();

	// PlayerとDragonFlyの当たり判定
	CheckPlayerDragonFly();

	// PlayerとKapuの当たり判定
	CheckPlayerKapu();

	// プレイヤーの弾とFliesの当たり判定
	CheckPlayerBulletFlies();

	// プレイヤーの弾とDragonFlyの当たり判定
	CheckPlayerBulletDragonFly();

	// プレイヤーの弾とKapuの当たり判定
	CheckPlayerBulletKapu();

	// エネミーの弾とプレイヤーの当たり判定
	CheckEnemyBulletPlayer();
}

