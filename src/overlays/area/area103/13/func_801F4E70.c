#include "area103_13.h"

MATCH void func_801F4E70(s32 arg0) {
    RECT rect;
    s32  idx;

    idx    = arg0 * 2;
    rect.x = D_801F5A14[idx] + 0x240;
    rect.y = D_801F5A15[idx] + 0x100;
    rect.w = 0x20;
    rect.h = 0x40;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, TASK_BYTES[0xB] * 0x30 + 0x240, 0x100);
    GFX_AddPrim(6, 0x18);
}
