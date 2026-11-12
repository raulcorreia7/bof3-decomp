#include "area052_13.h"

MATCH void func_801F3084(void) {
    AreaWorkRow* row;
    u16          angle;
    u8           i;

    angle = 0x80;
    for (i = 0; i < 4; i++) {
        row = (AreaWorkRow*)Area_FindFreeWorkRow();
        if (row != NULL) {
            row->active      = 1;
            row->unk_16      = 8;
            row->pos.x.fixed = g_Task->pos.x.fixed + (rcos(angle) << 4);
            row->pos.y.fixed = g_Task->pos.y.fixed + (rsin(angle) << 4);
            row->pos.z.fixed = g_Task->pos.z.fixed;
            row->unk_10      = 0x1800;
            row->unk_14      = 0xC0;
        }
        angle += 0x100;
    }
}
