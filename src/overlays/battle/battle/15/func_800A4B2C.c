#include "battle_15.h"

MATCH void func_800A4B2C(void) {
    u8* lock;

    lock = &D_80148624;
    if ((*lock & 1) == 0) {
        func_80097FE8();
        D_80148594 = 0;
        *lock      = 0;
        BattleStageMessageResource(g_BattleMessageSlot);
        /* FAKE: statement boundary keeps the retail register order and schedule. */
        ORDER_LOCK(g_BattleMessageState = 1);
        EMI_LoadArchive(EMI_SLOT_BATL_RE2);
        *(u8*)&g_BattleUIState += 1;
    }
}
