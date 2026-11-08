#include "area103_13.h"

MATCH void func_801F4E70(s32 arg) {
    RECT r;
    s32  idx;

    idx = arg * 2;
    r.x = D_801F5A14[idx] + 0x240;
    r.y = D_801F5A15[idx] + 0x100;
    r.w = 0x20;
    r.h = 0x40;
    SetDrawMove(g_GfxPrimCursor, &r, (TASK_BYTES[0xB] * 3) * 16 + 0x240, 0x100);
    GFX_AddPrim(6, 0x18);
}
