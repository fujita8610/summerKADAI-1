#pragma once

// �֐��̃v���g�^�C�v�錾

// ��`�Ɠ_�̓����蔻��
bool CheckSquarePoint(float squarePosX, float squarePosY, float squareWidth, float squareHeight, float pointX, float pointY);

// ��`�Ƌ�`�̓����蔻��
bool CheckSquareSquare(float squareA_PosX, float squareA_PosY, float squareA_Width, float squareA_Height, float squareB_PosX, float squareB_PosY, float squareB_Width, float squareB_Height);

// �~�Ɠ_�̓����蔻��
bool CheckCirclePoint(float circlePosX, float circlePosY, float circleRadius, float pointX, float pointY);

// �~�Ɖ~�̓����蔻��
bool CheckCircleCircle(float circleA_PosX, float circleA_PosY, float circleA_Radius, float circleB_PosX, float circleB_PosY, float circleB_Radius);

// �e�����蔻����s��
void CheckCollision();

