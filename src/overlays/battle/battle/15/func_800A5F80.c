#include "battle_15.h"

MATCH void func_800A5F80(void) {
    if (!(D_801485B8 & 0x1)) {
        func_80097FE8();
        D_80148594            = 0;
        D_801485DC            = 0;
        g_BattleSelectionHead = 0;
        D_801485DC            = 0;
        EMI_LoadArchive(EMI_SLOT_BATL_RE2);
        g_Battle.ui_step  = 4;
        g_Battle.ui_state = 3;
    }
}
