#include "area048_13.h"

MATCH void func_801F41F0(s32 page, s32 column) {
    RECT rect;
    s32  base;

    rect.x = (column + 1) * 8;
    base   = (page << 6) + 0x240;
    rect.x += base;
    rect.y = 352;
    rect.w = 8;
    rect.h = 0x78;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, base, 0x160);
    GFX_AddPrim(6U, sizeof(DR_MOVE));
}
