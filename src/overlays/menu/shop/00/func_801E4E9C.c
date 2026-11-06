#include "shop_00.h"

MATCH void func_801E4E9C(MenuPanelTask* panel_task) {
    s16          col;
    s32          row;
    s32          i;
    u8*          base;
    /* FAKE: volatile pointer stops extra IV. */
    volatile u8* slot;

    base = &D_80144952;
    UI_DrawWindow((u16)(panel_task->x + 3), (u16)(panel_task->y + 3), 114, 88, 0, base[0]);
    col  = 0;
    row  = 0;
    i    = 0;
    slot = base + 0x1B;
    do {
        /* FAKE: steer item read through base. */
        base = (u8*)slot;
        if ((slot[2] & 1) && (slot[0x16] == D_80148361)) {
            func_801E4FC8((u16)(panel_task->x + col + 4), (u16)(panel_task->y + row + 5), base[0], 0);
            col += 0x25;
            if (col >= 75) {
                col = 0;
                row += 0x2A;
            }
        }
        i += 1;
        slot += 0xA4;
    } while ((i & 0xFF) < 8U);
    Menu_DrawPanelFrame(panel_task->x, panel_task->y, 0xD, 0xA);
}
