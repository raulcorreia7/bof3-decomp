#include "area140_13.h"

MATCH void func_801F38C4(void) {
    s16 temp_v0;

    temp_v0                    = (u16)g_SpadWork->z.part.integer - 0x10;
    g_SpadWork->z.part.integer = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        Area_ClearCellPalette((s32)(s16)((u16)g_SpadWork->x.part.integer + 1),
                              (s32)(s16)((u16)g_SpadWork->y.part.integer + 1));
        g_SpadWork->state_02 = 1;
    }
    func_801F3950(g_SpadWork->direction_08, g_SpadWork->z.part.integer);
}
