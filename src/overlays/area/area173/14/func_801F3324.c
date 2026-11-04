#include "area173_14.h"

MATCH void func_801F3324(s32 source_y, s32 dest_y) {
    RECT rect;
    rect.x = 0x240;
    rect.w = 0x58;
    rect.y = source_y + 0x100;
    rect.h = 0x30;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x240, dest_y + 0x100);
    GFX_AddPrim(2, 0x18);
}
