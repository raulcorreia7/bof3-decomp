#include "area042_13.h"

MATCH void func_801F3D18(s32 column) {
    RECT rect;

    rect.x = (column * 8) + 0x1C8;
    rect.y = 352;
    rect.w = 8;
    rect.h = 0x78;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, D_801F5358[COORD_INT(g_Task->pos.x)] + 0x1C0, 0x160);
    GFX_AddPrim(6, 0x18);
}
