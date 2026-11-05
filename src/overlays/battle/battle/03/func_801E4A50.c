#include "battle_03.h"

MATCH void func_801E4A50(void) {
    if ((g_BattleCurrentEnemy->status & STATUS_KO) != 0u) {
        g_Task->mode = 6;
        g_Task->step = 4;
    } else {
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->mode = 2;
        g_Task->step = 0;
    }
    g_Task->unk_03 = 0;
}
