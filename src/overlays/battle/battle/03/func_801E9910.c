#include "battle_03.h"

MATCH void func_801E9910(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    Battle_DrawEnemyNamePanel((s16)panel->x, (s16)panel->y, ((u8*)panel)[0x0A]);
    if (g_BattleSelectionLatch != 0u) {
        if (D_801EB4D8->command.target == BATTLE_PANEL_TASK->cell_0A.slot) {
            func_801EA174();
        }
        if ((D_801EB4D8->command.target & 0x40u) != 0u) {
            func_801EA174();
        }
    }
}
