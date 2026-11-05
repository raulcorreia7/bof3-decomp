#include "battle_03.h"

MATCH void func_801D3BB4(void) {
    D_8014637C->step_01 = 0xC;
    Battle_SetSlotPending(g_BattleActingBattler);
    func_800AE2D4(g_BattleAction->unk_02);
    g_BattleUiStep += 1;
}
