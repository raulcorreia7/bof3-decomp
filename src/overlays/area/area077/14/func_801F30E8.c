#include "area077_14.h"

MATCH void func_801F30E8(s16 x0, s16 y0, s16 x1, s16 y1) {
    LINE_F2* line = (LINE_F2*)g_GfxPrimCursor;

    SetLineF2(line);
    SetSemiTrans(line, 1);
    line->r0 = D_801F6B6C;
    line->g0 = D_801F6B70;
    line->x0 = x0;
    line->y0 = y0;
    line->x1 = x1;
    line->y1 = y1;
    line->b0 = D_801F6B74;
    GFX_AddPrim(1, 16);
}
