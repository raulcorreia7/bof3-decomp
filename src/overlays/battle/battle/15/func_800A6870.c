#include "battle_15.h"

/* Sets g_BattlePanelMode to 4, g_UiPanelTasks[19].state to 2, g_Battle.ui_step to 3 and g_Battle.ui_mode to 2. */
MATCH void func_800A6870(void) {
    g_BattlePanelMode        = 4;
    g_UiPanelTasks[19].state = 2;
    g_Battle.ui_step         = 3;
    g_Battle.ui_mode         = 2;
}
