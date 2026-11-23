#include "area030_04.h"

/* Palette row table: 0x40-byte rows selected by the panel palette byte. */

/* Draws two semi-transparent rectangle outlines in the palette row colour, crossing the draw modes around the
 * shade flag. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D95C4(u16 x, u16 y, u16 w, u16 h, u8 shade) {
    LINE_F3* prim;
    u32      palette_offset;
    u16      color;
    s8       style;

    style          = MEM(s8, &g_WindowStyle);
    palette_offset = (style << 6) | 0x20;
    color          = MEM(u16, AREA_PALETTE_ARENA_33A00 + 8u + palette_offset);

    Fishing_SetDrawMode(shade ? 7 : 6, 2);
    prim = GFX_CURSOR(LINE_F3);
    SetLineF3(prim);
    /* No XY macro stores either run's corner order; spell both runs out. */
    prim->x1 = x + w;
    prim->x2 = x + w;
    prim->x0 = x;
    prim->y0 = y + h;
    prim->y1 = y + h;
    prim->y2 = y;
    setRGB0(prim, PSX_COLOR_R(color) << 3, PSX_COLOR_G(color) << 3, PSX_COLOR_B(color) << 3);
    PSX_SET_SEMI_TRANSPARENT(prim);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F3));

    Fishing_SetDrawMode(shade ? 6 : 7, 2);
    prim = GFX_CURSOR(LINE_F3);
    SetLineF3(prim);
    prim->x2 = x + w;
    prim->x0 = x;
    prim->x1 = x;
    prim->y0 = y + h;
    prim->y1 = y;
    prim->y2 = y;
    setRGB0(prim, PSX_COLOR_R(color) << 3, PSX_COLOR_G(color) << 3, PSX_COLOR_B(color) << 3);
    PSX_SET_SEMI_TRANSPARENT(prim);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F3));
}
#else
INCLUDE_ASM(func_801D95C4);
#endif
