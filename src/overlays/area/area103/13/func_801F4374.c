#include "area103_13.h"

MATCH void func_801F4374(void) {
    g_Task->x.fixed      = 0x430000;
    g_Task->y.fixed      = 0x1A0000;
    COORD_INT(g_Task->z) = -0x100;
    g_Task->unk_32       = 0x80;
    g_Task->unk_09       = 0;
    g_Task->unk_0B       = 1;
    Area_SetCellPalette(0x55, 0x19);
    g_Task->step += 1;
}
