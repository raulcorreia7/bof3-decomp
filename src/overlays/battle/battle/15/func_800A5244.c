#include "battle_15.h"

MATCH void func_800A5244(void) {
    volatile u8* latch;

    latch = &D_801485B8;
    if (!(*latch & 0x1)) {
        func_80097FE8();
        D_80148594            = 0;
        *latch                = 0;
        g_BattleSelectionHead = 0;
        D_801485DC            = 0;
        EMI_LoadArchive(EMI_SLOT_BATL_RE2);
        g_Battle.ui_step  = 4;
        g_Battle.ui_state = 3;
    }
}
