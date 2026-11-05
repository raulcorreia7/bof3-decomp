#include "area033_13.h"

MATCH void func_801F2E20(void) {
    s32 x;
    s32 y;
    s32 scaled;
    u8* scratch;

    scaled = D_80145E9C * D_80145E99;
    x      = (D_80145EC4[0] + scaled) >> 16;
    y      = (D_80145EC8 + D_80145EA0 * D_80145E99) >> 16;

    scratch                 = (u8*)g_SpadWork;
    *(s32*)(scratch + 0x0C) = x;
    *(s32*)(scratch + 0x10) = y;

    /* The step stores re-read the work cell: the compiler must assume a call
     * may have changed it. */
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {
        g_SpadWork->unk_0B = 1;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {
        g_SpadWork->unk_0B = 2;
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {
        g_SpadWork->unk_0B = 3;
    } else if (g_AreaWalkFlags & AREA_WALK_TRANSITION) {
        g_SpadWork->unk_0B = 4;
    } else {
        g_SpadWork->unk_0B = 0;
    }

    D_801F4F64[g_SpadWork->unk_01]();
}
