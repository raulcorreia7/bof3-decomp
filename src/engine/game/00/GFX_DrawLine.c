#include "game_00.h"

MATCH void GFX_DrawLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, s32 blend) {
    LINE_F2* line;
    s32      tpage;

    tpage = getTPage(0, blend, 896, 256);
    GFX_AddDrawMode(tpage);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    setXY2(line, x0, y0, x1, y1);
    setRGB0(line, r, g, b);
    SetSemiTrans(line, 1);
    GFX_AddPrim(1U, 0x10U);
}
