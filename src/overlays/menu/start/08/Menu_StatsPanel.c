#include "start_08.h"

void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index);

/* func_801E96CC */
MATCH void Menu_StatsPanel(void) {
    g_MenuStartStatsSteps[g_UIPanelCurrent->state]();
    Menu_DrawStatPanel(g_UIPanelCurrent->pos.vx, g_UIPanelCurrent->pos.vy, g_CharSlot[g_PartyFieldOrder[g_UIPanelCurrent->unk_0A]]);
}
