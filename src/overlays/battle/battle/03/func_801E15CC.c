#include "battle_03.h"

MATCH void func_801E15CC(void) {
    func_801DEDE4();
    if (HAS_STATUS(*g_GameState, STATUS_KO)) {
        g_Task->mode = 6;
        g_Task->step = 4;
    } else {
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->mode = 3;
        g_Task->step = 0;
    }
    g_Task->unk_03 = 0;
}
