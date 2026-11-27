#include "battle_03.h"

/* Per-panel (x, y) offsets of the five panels. */

/* draws the five panels at the panel position plus the per-panel offsets, then ages the panel widths or
 * advances the panel state when the first panel width has run out.
 */
/* func_801E927C */
MATCH void Battle_DrawMenuPanels(void) {
    u8 i;
    u8 size;
    u8 xoff;
    u8 yoff;

    for (i = 0; i < 5; i++) {
        size = g_Battle.panel_widths[i];
        xoff = s_BattlePanelOffsets[i][0];
        yoff = s_BattlePanelOffsets[i][1];
        UI_IconDrawCell(i, (u16)((size >> 1) + (g_UIPanelCurrent->pos.vx + xoff)), (u16)((size >> 1) + (g_UIPanelCurrent->pos.vy + yoff)), (u8)(0x10 - size), (u8)(0x10 - size), GFX_COLOR_NEUTRAL);
    }
    i = 0;
    if (g_Battle.panel_widths[0] == 0) {
        g_UIPanelCurrent->state++;
    } else {
        do {
            g_Battle.panel_widths[i]--;
            i++;
        } while (i < 7);
    }
}
