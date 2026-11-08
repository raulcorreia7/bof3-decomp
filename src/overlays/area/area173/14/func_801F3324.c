#include "area173_14.h"

MATCH void func_801F3324(s32 source_y, s32 dest_y) {
    RECT rect;
    rect.x = 576;
    rect.w = 88;
    rect.y = source_y + 256;
    rect.h = 48;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 576, dest_y + 256);
    GFX_AddPrim(2, sizeof(DR_MOVE));
}
