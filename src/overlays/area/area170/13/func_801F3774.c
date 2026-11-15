#include "area170_13.h"

MATCH void func_801F3774(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b, u8 semi_trans) {
    LINE_F2* line;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, semi_trans);
    setXY2(line, x0, y0, x1, y1);
    setRGB0(line, r, g, b);
    GFX_AddPrim(2, sizeof(LINE_F2));
}
