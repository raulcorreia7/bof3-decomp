#include "battle_03.h"

MATCH void func_801E15CC(void) {
    func_801DEDE4();
    if (HAS_STATUS(*g_Game.current, STATUS_KO)) {
        g_Task->header.mode = 6;
        g_Task->header.step = 4;
    } else {
        Battle_ClearSlotPending(g_Task->slot);
        g_Task->header.mode = 3;
        g_Task->header.step = 0;
    }
    g_Task->unk_03 = 0;
}
