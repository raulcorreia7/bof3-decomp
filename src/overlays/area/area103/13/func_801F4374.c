#include "area103_13.h"

MATCH void func_801F4374(void) {
    g_Task->pos.x.fixed      = TO_COORD(67);
    g_Task->pos.y.fixed      = TO_COORD(26);
    COORD_INT(g_Task->pos.z) = -0x100;
    g_Task->unk_32           = 0x80;
    g_Task->timer            = 0;
    g_Task->param.unk_0B     = 1;
    Area_SetCellPalette(85, 25);
    g_Task->header.step += 1;
}
