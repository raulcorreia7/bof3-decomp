#include "battle_03.h"

/* Per-row (x, y) offsets of the five panel rows. */

/* draws the five panel rows at the panel position plus the per-row offsets, then ages the row counters or
 * advances the panel state when the first row has run out.
 */
/* func_801E927C */
MATCH void Battle_DrawMenuRows(void) {
    u8 i;
    u8 size;
    u8 xoff;
    u8 yoff;

    for (i = 0; i < 5; i++) {
        size = g_Battle.panel_widths[i];
        xoff = s_BattlePanelOffsets[i][0];
        yoff = s_BattlePanelOffsets[i][1];
        func_801644D8(i, (u16)((size >> 1) + (g_MenuCurrentPanel->pos.x + xoff)), (u16)((size >> 1) + (g_MenuCurrentPanel->pos.y + yoff)), (u8)(0x10 - size), (u8)(0x10 - size), 0x80);
    }
    i = 0;
    if (g_Battle.panel_widths[0] == 0) {
        g_MenuCurrentPanel->state++;
    } else {
        do {
            g_Battle.panel_widths[i]--;
            i++;
        } while (i < 7);
    }
}
