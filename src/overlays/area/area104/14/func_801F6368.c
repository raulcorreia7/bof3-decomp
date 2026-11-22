#include "area104_14.h"

/* Draws a pulsing fan of 24 translucent red triangles around the leader's screen position. */
MATCH void func_801F6368(void) {
    POLY_F3* prim;
    s32      angle;
    s32      i;
    s32      centre_x;
    s32      centre_y;
    s32      x;
    s32      y;
    s32      radius;
    s32      shade;
    s32      tpage;

    x        = g_Game.members[0].pos.x.part.integer - 0x25;
    y        = g_Game.members[0].pos.y.part.integer - 0x2D;
    centre_x = (((x - y) * rcos(0x200)) >> 12) + 0xFA;
    centre_y = (((x + y) * rcos(0x200)) >> 12) + 0xAF;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xAE;
    } else {
        tpage = 0x3E;
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);

    radius = 8 - ((g_FrameCount >> 1) & 7);
    shade  = ~(radius * 0x1E);
    i      = 0;
loop:
    prim = (POLY_F3*)g_GfxPrimCursor;
    setPolyF3(prim);
    SetSemiTrans(prim, 1);
    angle    = i * 0xAA;
    prim->x0 = centre_x;
    prim->y0 = centre_y;
    prim->x1 = centre_x + ((radius * rcos(angle)) >> 12);
    prim->y1 = centre_y + ((radius * rsin(angle)) >> 12);
    i++;
    angle    = i * 0xAA;
    prim->x2 = centre_x + ((radius * rcos(angle)) >> 12);
    prim->y2 = centre_y + ((radius * rsin(angle)) >> 12);
    setRGB0(prim, shade, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_F3));
    if (i < 0x18) {
        goto loop;
    }
}
