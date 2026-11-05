#include "battle_03.h"

MATCH void func_801E9910(void) {
    MenuPanelTask* panel;

    panel = g_MenuPanelTaskCurrent;
    Battle_DrawEnemyNamePanel((s32)(s16)panel->x, (s32)(s16)panel->y, ((u8*)panel)[0x0A]);
    if (g_BattleSelectionLatch != 0u) {
        if (*D_801EB4D8 == BATTLE_PANEL_TASK->cell_0A.slot) {
            func_801EA174();
        }
        if ((*D_801EB4D8 & 0x40u) != 0u) {
            func_801EA174();
        }
    }
}
