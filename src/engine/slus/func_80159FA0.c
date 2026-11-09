#include "engine/slus/slus.h"

/* draws a flat-coloured F4 quad into the current primitive. */
MATCH void func_80159FA0(s32 x, s32 y, u8 width, u8 height) {
    LINE_F4* line;
    s32      x0;
    s32      y0;
    s32      x1;
    s32      y1;

    line = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line);
    x0 = x - 1;
    y0 = y - 1;
    x1 = x + width + 1;
    y1 = y + height + 1;
    setRGB0(line, 120, 120, 120);
    setXY4(line, x0, y0, x1, y0, x1, y1, x0, y1);
    GFX_AddPrim(1u, sizeof(LINE_F4));
    UI_DrawLine(x0, y0, x0, y1, 0x78);
}
