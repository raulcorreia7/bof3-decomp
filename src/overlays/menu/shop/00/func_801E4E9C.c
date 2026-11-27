#include "shop_00.h"

MATCH void func_801E4E9C(MenuPanelTask* panel_task) {
    s16          col;
    s32          row;
    s32          i;
    u8*          base;
    /* FAKE: volatile pointer stops extra IV. */
    volatile u8* slot;

    base = &g_WindowStyle;
    UI_WindowDraw((u16)(panel_task->pos.vx + 3), (u16)(panel_task->pos.vy + 3), 114, 88, 0, base[0]);
    col  = 0;
    row  = 0;
    i    = 0;
    slot = base + 0x1B;
    do {
        /* FAKE: steer item read through base. */
        base = (u8*)slot;
        if ((slot[2] & 0x1) && (slot[0x16] == g_UiPanelTasks[1].flags)) {
            func_801E4FC8((u16)(panel_task->pos.vx + col + 4), (u16)(panel_task->pos.vy + row + 5), base[0], 0);
            col += 0x25;
            if (col >= 75) {
                col = 0;
                row += 42;
            }
        }
        i += 1;
        slot += 164;
    } while ((i & BYTE_MASK) < 8U);
    Menu_DrawPanelFrame(panel_task->pos.vx, panel_task->pos.vy, 13, 10);
}
