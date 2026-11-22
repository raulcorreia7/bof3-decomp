#include "battle_03.h"

MATCH void func_801D3168(void) {
    Battle_SetSlotPending(g_Battle.active_battler);
    D_8014637C->header.mode = 4;
    g_Battle.phase.mode     = BATTLE_MODE_TURNS;
    g_Battle.phase.step     = 2;
    g_Battle.phase.sub_step = 0;
}
