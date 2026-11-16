#include "area030_04.h"

/* Palette row table: 0x40-byte rows selected by the panel palette byte. */

/* Draws two semi-transparent rectangle outlines in the palette row colour, crossing the draw modes around the
 * shade flag. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D95C4(u16 x, u16 y, u16 w, u16 h, u8 shade) {
    LINE_F3* prim;
    u16      y_origin;
    u16      color;
    s32      mode;
    s32      r;
    s32      g;
    s32      b;

    color = ((u16*)&D_80033A08)[(((u32)((*(s8*)&g_WindowStyle) << 6)) | 0x20) >> 1];
    r     = (color & 0x1F) << 3;
    g     = (color >> 2) & 0xF8;
    b     = (color >> 7) & 0xF8;

    if (shade != 0) {
        mode = 7;
    } else {
        mode = 6;
    }
    Fishing_SetDrawMode(mode, 2);
    prim     = (LINE_F3*)g_GfxPrimCursor;
    y_origin = y;
    SetLineF3(prim);
    prim->x2 = (prim->x1 = x + w);
    prim->x0 = x;
    prim->y1 = (prim->y0 = y_origin + h);
    prim->y2 = y;
    setRGB0(prim, r, g, b);
    SetSemiTrans(prim, 1);
    GFX_AddPrim(2, sizeof(LINE_F3));

    if (shade != 0) {
        mode = 6;
    } else {
        mode = 7;
    }
    Fishing_SetDrawMode(mode, 2);
    prim = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(prim);
    prim->x2 = x + w;
    prim->x1 = (prim->x0 = x);
    prim->y0 = y + h;
    prim->y2 = (prim->y1 = y);
    setRGB0(prim, r, g, b);
    SetSemiTrans(prim, 1);
    GFX_AddPrim(2, sizeof(LINE_F3));
}
#else
INCLUDE_ASM(func_801D95C4);
#endif
