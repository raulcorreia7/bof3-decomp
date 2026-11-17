#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F6368(void) {
    POLY_G3* prim;
    s32      i;
    s32      centre_x;
    s32      centre_y;
    s32      x;
    s32      y;
    s32      radius;
    s32      shade;
    s32      tpage;

    x = g_Game.members[0].pos.x.part.integer;
    y = g_Game.members[0].pos.y.part.integer;
    x -= 0x25;
    y -= 0x2D;
    centre_x = (((x - y) * rcos(0x200)) >> 12) + 0xFA;
    centre_y = (((x + y) * rcos(0x200)) >> 12) + 0xAF;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);

    radius = 8 - ((g_FrameCount >> 1) & 7);
    shade  = ~(radius * 0x1E);
    i      = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = centre_x;
        prim->y0 = centre_y;
        prim->x1 = centre_x + ((radius * rcos(i * 0xAA)) >> 12);
        prim->y1 = centre_y + ((radius * rsin(i * 0xAA)) >> 12);
        i++;
        prim->x2 = centre_x + ((radius * rcos(i * 0xAA)) >> 12);
        prim->y2 = centre_y + ((radius * rsin(i * 0xAA)) >> 12);
        setRGB0(prim, shade, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
    } while (i < 0x18);
}
#else
INCLUDE_ASM(func_801F6368);
#endif
