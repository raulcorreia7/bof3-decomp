#include "game_00.h"

MATCH void GFX_DrawLine(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, s32 blend) {
    LINE_F2* line;
    s32      tpage;

    tpage = getTPage(0, blend, 896, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, NULL);
    GFX_AddPrim(1U, 0xCU);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    line->x0 = x0;
    line->y0 = y0;
    line->x1 = x1;
    line->y1 = y1;
    line->r0 = r;
    line->g0 = g;
    line->b0 = b;
    PSX_SET_SEMI_TRANSPARENT(line);
    GFX_AddPrim(1U, 0x10U);
}
