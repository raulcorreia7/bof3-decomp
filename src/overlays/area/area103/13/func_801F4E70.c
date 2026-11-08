#include "area103_13.h"

MATCH void func_801F4E70(s32 frame) {
    RECT rect;
    s32  idx;

    idx    = frame * 2;
    rect.x = D_801F5A14[idx] + 576;
    rect.y = D_801F5A15[idx] + 256;
    rect.w = 32;
    rect.h = 64;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, g_Task->param.unk_0B * 48 + 576, 256);
    GFX_AddPrim(6, 24);
}
