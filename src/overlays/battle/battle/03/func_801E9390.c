#include "battle_03.h"

MATCH void func_801E9390(void) {
    u8*            mode;
    s32            i;
    s32            index;
    u8             grow;
    u8             decay;
    MenuPanelTask* task;

    i    = 0;
    /* Retail materialises &g_Battle.panel_slot once before the loop and reloads the
     * byte on every iteration; a plain scalar read repeats lui plus the load. */
    mode = &g_Battle.panel_slot;
    do {
        index = i & BYTE_MASK;
        if (*mode == index) {
            grow = g_Battle.panel_widths[index];
            if (grow < 8u) {
                g_Battle.panel_widths[index] = grow + 2;
            }
        } else {
            decay = g_Battle.panel_widths[index];
            if (decay != 0) {
                g_Battle.panel_widths[index] = decay - 2;
            }
        }
        i += 1;
    } while ((i & BYTE_MASK) < 7u);
    task = g_MenuCurrentPanel;
    Battle_DrawPanelRows(task->pos.x, task->pos.y);
}
