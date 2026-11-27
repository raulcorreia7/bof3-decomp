#include "battle_15.h"

/* func_800A4B2C */
MATCH void Battle_LoadRe2Archive(void) {
    u8* lock;

    lock = &g_UiPanelTasks[21].active;
    if ((*lock & 0x1) == 0) {
        func_80097FE8();
        g_UiPanelTasks[17].active = 0;
        *lock                     = 0;
        Battle_ShowMessage(g_BattleMessageSlot);
        /* FAKE: statement boundary keeps the retail register order and schedule. */
        do {
            g_BattleMessageState = 1;
        } while (0);
        EMI_ArchiveLoad(EMI_SLOT_BATL_RE2);
        g_Battle.ui_mode += 1;
    }
}
