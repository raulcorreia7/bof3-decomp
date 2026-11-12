#include "battle_15.h"

MATCH void func_800A5874(void) {
    u8*          latch;
    volatile u8* counter;

    latch = &D_80148624;
    if ((*latch & 0x1) == 0) {
        func_80097FE8();
        D_80148594            = 0;
        *latch                = 0;
        g_BattleSelectionHead = 0;
        D_801485DC            = 0;
        EMI_LoadArchive(EMI_SLOT_BATL_RE2);
        counter  = &g_Battle.ui_state;
        *counter = *counter + 1;
    }
}
