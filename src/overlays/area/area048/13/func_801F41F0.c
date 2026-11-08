#include "area048_13.h"

MATCH void func_801F41F0(s32 arg0, s32 arg1) {
    RECT rect;
    s32  base;

    rect.x = (arg1 + 1) * 8;
    base   = (arg0 << 6) + 0x240;
    rect.x += base;
    rect.y = 0x160;
    rect.w = 8;
    rect.h = 0x78;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, base, 0x160);
    GFX_AddPrim(6U, 0x18U);
}
