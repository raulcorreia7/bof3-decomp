#include "battle_15.h"

/* func_800A4B2C */
MATCH void Battle_LoadRe2Archive(void) {
    u8* lock;

    lock = &D_80148624;
    if ((*lock & 0x1) == 0) {
        func_80097FE8();
        D_80148594 = 0;
        *lock      = 0;
        Battle_ShowMessage(g_BattleMessageSlot);
        /* FAKE: statement boundary keeps the retail register order and schedule. */
        FAKE_ORDER_LOCK(g_BattleMessageState = 1);
        EMI_LoadArchive(EMI_SLOT_BATL_RE2);
        *(u8*)&g_Battle.ui_state += 1;
    }
}
