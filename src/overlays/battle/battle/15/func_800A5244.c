#include "battle_15.h"

MATCH void func_800A5244(void) {
    volatile u8* latch;

    latch = &g_UiPanelTasks[18].active;
    if (!(*latch & 0x1)) {
        func_80097FE8();
        g_UiPanelTasks[17].active        = 0;
        *latch                           = 0;
        g_BattleChoicePanel.items.active = 0;
        g_UiPanelTasks[19].active        = 0;
        EMI_ArchiveLoad(EMI_SLOT_BATL_RE2);
        g_Battle.ui_step = 4;
        g_Battle.ui_mode = 3;
    }
}
