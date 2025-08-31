#include "SlotMachine.h"
#include "../夏休み課題１/so-su/player.h"
#include "DxLib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "corecrt_stdio_config.h"


enum Symbol {
    SYMBOL_SEVEN,
    SYMBOL_BAR,
    SYMBOL_CHERRY,
    SYMBOL_BELL,
    SYMBOL_NONE
};

enum Outcome {
    OUTCOME_BB,      // Big Bonus
    OUTCOME_RB,      // Regular Bonus
    OUTCOME_CHANCE,  // Chance
    OUTCOME_BELL,    // Bell
    OUTCOME_NONE     // No win
};


Outcome g_nextOutcome = OUTCOME_NONE;

struct Reel
{
    std::vector<Symbol> symbols;
    int currentPos;
};

Reel g_reels[NUM_REELS];
bool g_isSpinning = false;
int g_spinTimer = 0;




void InitSlotReels()
{



    // 各リールのシンボルを設定
    g_reels[0].symbols = { SYMBOL_SEVEN, SYMBOL_BAR, SYMBOL_CHERRY, SYMBOL_BELL, SYMBOL_NONE };
    g_reels[1].symbols = { SYMBOL_SEVEN, SYMBOL_BAR, SYMBOL_CHERRY, SYMBOL_BELL, SYMBOL_NONE };
    g_reels[2].symbols = { SYMBOL_SEVEN, SYMBOL_BAR, SYMBOL_CHERRY, SYMBOL_BELL, SYMBOL_NONE };
    // 各リールの初期位置をランダムに設定
    for (int i = 0; i < NUM_REELS; i++) {
        g_reels[i].currentPos = GetRand(g_reels[i].symbols.size() - 1);
    }

	
}

void StartSlotMachine()
{
    if (!g_isSpinning) {
        g_isSpinning = true;
        g_spinTimer = SLOT_SPIN_TIME;

    
        // 次の結果をランダムに決定
        int i = GetRand(99); //0^99の乱数を取得
        if (i < 80)
        {
            g_nextOutcome = OUTCOME_NONE;
        }
        else if (i < 95)
        {
            g_nextOutcome = OUTCOME_BELL;
        }
        else if (i >= 95)
        {
            g_nextOutcome = OUTCOME_CHANCE;
            int j = GetRand(10);
            if (j < 9)
            {
                g_nextOutcome = OUTCOME_RB;
            }
            else
            {
                g_nextOutcome = OUTCOME_BB;
            }
        }
      
    }
}

void UpdateSlotMachine()
{
    if (g_isSpinning) {
        for (int i = 0; i < NUM_REELS; i++)
        {
            g_reels[i].currentPos
                = (g_reels[i].currentPos + 1)
                % g_reels[i].symbols.size();
        }

        g_spinTimer--;
        if (g_spinTimer <= 0) {
            g_isSpinning = false;
            CheckSlotResult();
        }
    }
}

void CheckSlotResult()
{
    switch (g_nextOutcome)
    {
    case OUTCOME_BB:
    {

        SlotBB();
        g_reels[0].currentPos = 0; // 7
        g_reels[1].currentPos = 0; // 7
        g_reels[2].currentPos = 0; // 7

        break;
    }

    case OUTCOME_RB:
    {
        SlotRB();
        int rbType = GetRand(1);
        if (rbType == 0)
        {
            g_reels[0].currentPos = 0; // 7
            g_reels[1].currentPos = 0; // 7
            g_reels[2].currentPos = 1; // BAR
        }
        else
        {
            g_reels[0].currentPos = 2; // CHERRY
            g_reels[1].currentPos = 2; // CHERRY
            g_reels[2].currentPos = 2; // CHERRY
        }

        break;
    }

    case OUTCOME_CHANCE:
    {
        SlotCHERRY();
        int chanceType = GetRand(2);
        if (chanceType == 0)
        {
            g_reels[0].currentPos = 2; // CHERRY
            g_reels[1].currentPos = 4; // CHERRY
            g_reels[2].currentPos = 4; // BAR
        }
        else if (chanceType == 1)
        {
            g_reels[0].currentPos = 4; // CHERRY
            g_reels[1].currentPos = 2; // BAR
            g_reels[2].currentPos = 4; // CHERRY
        }
        else
        {
            g_reels[0].currentPos = 4; // BAR
            g_reels[1].currentPos = 4; // CHERRY
            g_reels[2].currentPos = 2; // CHERRY
        }

        break;
    }
    case OUTCOME_BELL:
    {
        SlotBELL();
        g_reels[0].currentPos = 3; // BELL
        g_reels[1].currentPos = 3; // BELL
        g_reels[2].currentPos = 3; // BELL

        break;
    }
    case OUTCOME_NONE:


        g_reels[0].currentPos = 4; 
        g_reels[1].currentPos = 4; 
        g_reels[2].currentPos = 4; 

        break;

    }
}

    void DrawSlotMachine()
    {
        int baseX = 1000; // 右下の座標（画面サイズに合わせて調整）
        int baseY = 600;
        int reelWidth = 80;
        int reelHeight = 120;

        for (int i = 0; i < NUM_REELS; i++)
        {
            DrawBox(baseX + i * (reelWidth + 10), baseY,
                baseX + i * (reelWidth + 10) + reelWidth,
                baseY + reelHeight,
                GetColor(50, 50, 50), TRUE);

            DrawString(baseX + i * (reelWidth + 10) + 20,
                baseY + 40,
                GetSymbolText(g_reels[i].symbols[g_reels[i].currentPos]),
                GetColor(255, 255, 0));
        }
    }


const char* GetSymbolText(Symbol symbol)
{
    switch (symbol) {
    case SYMBOL_SEVEN: return "7";
    case SYMBOL_BAR: return "BAR";
    case SYMBOL_CHERRY: return "CHERRY";
	case SYMBOL_BELL: return "BELL";
    default: return "---";
    }
}


