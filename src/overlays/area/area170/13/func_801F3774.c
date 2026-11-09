#include "area170_13.h"

MATCH void func_801F3774(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, u8 semi_trans) {
    LINE_F2* line;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, semi_trans);
    line->x0 = x0;
    line->y0 = y0;
    line->x1 = x1;
    line->y1 = y1;
    line->r0 = r;
    line->g0 = g;
    line->b0 = b;
    GFX_AddPrim(2, sizeof(LINE_F2));
}
