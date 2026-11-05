#include "area140_13.h"

MATCH void func_801F34F4(void) {
    s16 height;

    height                     = (u16)g_SpadWork->z.part.integer + 0x10;
    g_SpadWork->z.part.integer = height;
    if (height >= 0x80) {
        Area_SetCellPalette((s32)g_SpadWork->x.part.integer, (s32)g_SpadWork->y.part.integer);
        Area_ClearCellPalette((s32)(s16)((u16)g_SpadWork->x.part.integer + 1),
                              (s32)(s16)((u16)g_SpadWork->y.part.integer + 1));
        g_SpadWork->state_02 += 1;
    }
    func_801F3950(g_SpadWork->direction_08, g_SpadWork->z.part.integer);
}
