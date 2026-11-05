#include "area103_13.h"

MATCH void func_801F4374(void) {
    g_SpadWork->x.fixed        = 0x430000;
    g_SpadWork->y.fixed        = 0x1A0000;
    g_SpadWork->z.part.integer = -0x100;
    g_SpadWork->unk_32         = 0x80;
    g_SpadWork->unk_09         = 0;
    g_SpadWork->unk_0B         = 1;
    Area_SetCellPalette(0x55, 0x19);
    g_SpadWork->state_02 += 1;
}
