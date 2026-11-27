#include "battle_15.h"

MATCH void func_800A5874(void) {
    u8*          latch;
    volatile u8* counter;

    latch = &g_UiPanelTasks[21].active;
    if ((*latch & 0x1) == 0) {
        func_80097FE8();
        D_80148594                       = 0;
        *latch                           = 0;
        g_BattleChoicePanel.items.active = 0;
        g_UiPanelTasks[19].active                       = 0;
        EMI_ArchiveLoad(EMI_SLOT_BATL_RE2);
        counter  = &g_Battle.ui_mode;
        *counter = *counter + 1;
    }
}
