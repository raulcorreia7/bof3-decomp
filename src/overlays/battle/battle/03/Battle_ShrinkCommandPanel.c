#include "battle_03.h"

/* func_801D22E8 */
MATCH void Battle_ShrinkCommandPanel(void) {
    u8 value;

    value = g_Battle.panel_widths[g_Battle.panel_slot];
    if (value != 0) {
        g_Battle.panel_widths[g_Battle.panel_slot] = value - 2;
    } else {
        g_Battle.phase.sub_step += 1;
    }
    func_801D8450(g_Battle.panel_slot);
    Battle_DrawPartyPanel(g_UIPanelTasks[1].pos.vx, g_UIPanelTasks[1].pos.vy);
    Battle_DrawPanels(g_UIPanelTasks[2].pos.vx, g_UIPanelTasks[2].pos.vy);
}
