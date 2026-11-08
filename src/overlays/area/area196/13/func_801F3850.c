#include "area196_13.h"

MATCH void func_801F3850(void) {
    RECT rect;

    rect.x = 424;
    rect.y = 320 - (g_Task->unk_0A >> 1);
    rect.w = 16;
    rect.h = 32;
    SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x198, 0x120);
    GFX_AddPrim(2, sizeof(DR_MOVE));
}
