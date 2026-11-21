#include "engine/slus/slus.h"

/* Draws the grey outline of the box at x, y of width by height. */
/* func_80159FA0 */
MATCH void UI_DrawBoxOutline(s32 x, s32 y, u8 width, u8 height) {
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
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F4));
    UI_DrawLine(x0, y0, x0, y1, 0x78);
}
