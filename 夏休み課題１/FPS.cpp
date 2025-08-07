#include"DxLib.h"
#include"so-su/FPS/FPS.h"

// ���ς��v�Z����^�C�~���O�i��̂�FPS�Ɠ�������OK�j
#define FPS_SAMPLE_NUM (60) // 60�t���[���Ɉ�x���ς��v�Z����

// �Q�[����FPS
#define FPS (60)

int g_StartTime;      // ����J�n����
int g_Count;          // �J�E���^
float g_Fps;          // ���݂�FPS

void InitFPS()
{
    g_StartTime = GetNowCount();
    g_Count = 0;
    g_Fps = 0;
}

void UpdateFPS()
{
    // 1�t���[���ڂȂ玞�����L��
    if (g_Count == 0)
    {
        g_StartTime = GetNowCount();
    }

    // �T���v�����Ɠ����񐔃t���[����������畽�ς��v�Z����
    if (g_Count == FPS_SAMPLE_NUM) {
        int time = GetNowCount();
        // �����������ԁi�ؕb�j���T���v�����Ŋ��蕽�ςƂ���i���̒l�����݂�FPS�l�j
        g_Fps = 1000.f / ((time - g_StartTime) / (float)FPS_SAMPLE_NUM);
        g_Count = 0;
        g_StartTime = time;
    }
    g_Count++;

}

void DrawFPS()
{
    DrawFormatString(0, 0, GetColor(255, 255, 255), "FPS�y%.1f�z", g_Fps);
}

void FPSWait()
{
    // ������������
    int takeTime = GetNowCount() - g_StartTime;

    // �ҋ@����
    // FPS�̒l����1�t���[���ɂ������Ăق������ԁig_Count * 1000 / FPS�j
    // ���ۂɌo�߂������ԁitakeTime�j
    // ���ۂ̎��Ԃ����������ꍇ�́A���̍�����ҋ@���ԂƂ���
    int waitTime = g_Count * 1000 / FPS - takeTime;

    // �ҋ@
    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}
