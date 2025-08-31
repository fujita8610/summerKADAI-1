

#include <vector>
// スロットの設定
#define NUM_REELS 3
#define SLOT_SPIN_TIME 180  // スロット回転時間（フレーム）

enum Symbol;
struct Reel;

extern Reel g_reels[NUM_REELS];
extern bool g_isSpinning;
extern int g_spinTimer;

void InitSlotReels();
void StartSlotMachine();
void UpdateSlotMachine();
void DrawSlotMachine();
void CheckSlotResult();

const char* GetSymbolText(Symbol symbol);

