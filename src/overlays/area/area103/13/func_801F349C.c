#include "area103_13.h"

MATCH void func_801F349C(void) {
    AreaEffectRow* row = (AreaEffectRow*)AREA_WORK_WINDOW_ADDRESS;
    u8             i;
    /* FAKE: retail reserves 0x10 frame bytes nothing in the body uses. */
    STACK_PADS(u8, 16);

    for (i = 0; i < 3; i++) {
        row->x      = g_SpadWork->x.fixed;
        row->y      = g_SpadWork->y.fixed;
        row->z      = g_SpadWork->z.fixed + 0x03800000;
        row->angle  = (i << 12) / 3;
        row->scale  = 0xC00;
        row->unk_14 = 0;
        row++;
    }
}
