#include "battle_03.h"

/* Per-row (x, y) offsets of the five panel rows. */

/* draws the five panel rows at the panel position plus the per-row offsets, then ages the row counters or
 * advances the panel state when the first row has run out.
 */
MATCH void func_801E927C(void) {
    u8 i;
    u8 size;
    u8 xoff;
    u8 yoff;

    for (i = 0; i < 5; i++) {
        size = g_BattlePanelWidths[i];
        xoff = s_BattlePanelOffsets[i][0];
        yoff = s_BattlePanelOffsets[i][1];
        func_801644D8(i, (u16)((size >> 1) + (g_MenuCurrentPanel->x + xoff)),
                      (u16)((size >> 1) + (g_MenuCurrentPanel->y + yoff)), (u8)(0x10 - size), (u8)(0x10 - size), 0x80);
    }
    i = 0;
    if (g_BattlePanelWidths[0] == 0) {
        g_MenuCurrentPanel->state++;
    } else {
        do {
            g_BattlePanelWidths[i]--;
            i++;
        } while (i < 7);
    }
}
