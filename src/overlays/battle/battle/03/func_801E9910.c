#include "battle_03.h"

MATCH void func_801E9910(void) {
    MenuPanelTask* panel;

    panel = g_MenuCurrentPanel;
    Battle_DrawEnemyNamePanel((s16)panel->pos.x, (s16)panel->pos.y, ((u8*)panel)[0x0A]);
    if (g_BattleSelectionLatch != 0u) {
        if (g_BattleActorTurn->command.target == BATTLE_PANEL_TASK->cell_0A.slot) {
            func_801EA174();
        }
        if ((g_BattleActorTurn->command.target & BATTLE_TARGET_ENEMY_SIDE) != 0u) {
            func_801EA174();
        }
    }
}
