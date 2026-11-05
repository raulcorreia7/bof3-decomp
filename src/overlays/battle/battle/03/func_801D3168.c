#include "battle_03.h"

MATCH void func_801D3168(void) {
    Battle_SetSlotPending(g_BattleActingBattler);
    D_8014637C->step_01 = 4;
    g_BattleMode        = 3;
    g_BattleStep        = 2;
    g_BattleSubStep     = 0;
}
