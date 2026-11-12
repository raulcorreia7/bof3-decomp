#include "battle_03.h"

MATCH void func_801DA5A8(s16 x0, s16 y0, s16 x1, s16 y1, u8 r, u8 g, u8 b) {
    LINE_F2* primitive;

    GFX_AddDrawMode(GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y));
    primitive = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(primitive);
    setRGB0(primitive, r, g, b);
    setXY0(primitive, x0, y0);
    primitive->x1 = x1;
    primitive->y1 = y1;
    SetSemiTrans(primitive, 1);
    GFX_AddPrim(1, sizeof(LINE_F2));
}
