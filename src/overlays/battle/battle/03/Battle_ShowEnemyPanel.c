#include "battle_03.h"

/* func_801E9910 */
MATCH void Battle_ShowEnemyPanel(void) {
    MenuPanelTask* panel;

    panel = g_UIPanelCurrent;
    Battle_DrawEnemyNamePanel(panel->pos.vx, panel->pos.vy, panel->unk_0A);
    if (g_Battle.selection_latch != 0u) {
        if (g_BattleActorTurn->command.target == BATTLE_PANEL_TASK->selection.slot) {
            Battle_LightPanel();
        }
        if ((g_BattleActorTurn->command.target & BATTLE_TARGET_ENEMY_SIDE) != 0u) {
            Battle_LightPanel();
        }
    }
}
