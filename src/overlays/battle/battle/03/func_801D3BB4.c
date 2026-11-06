#include "battle_03.h"

MATCH void func_801D3BB4(void) {
    D_8014637C[1] = 0xC;
    Battle_SetSlotPending(g_BattleActiveBattler);
    func_800AE2D4(g_BattleAction->unk_02);
    g_BattleUIStep += 1;
}
