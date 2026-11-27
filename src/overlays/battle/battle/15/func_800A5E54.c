#include "battle_15.h"

MATCH void func_800A5E54(void) {
    u8* state;

    if (!(g_UIPanelTasks[19].active & 0x1)) {
        state            = &g_Battle.selection;
        g_Battle.ui_step = 2;
        g_Battle.ui_mode = 0;
        *state &= 0x7F;
    }
}
