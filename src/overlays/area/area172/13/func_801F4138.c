#include "area172_13.h"

MATCH void func_801F4138(s16 centre_x, s16 centre_y, s16 radius, s16 centre_shade, s16 arc_shade) {
    POLY_G3* prim;
    s32      phase;
    u8       centre_color;
    u8       arc_color;
    u8       i;

    if (centre_shade < 0) {
        centre_color = 0;
    } else {
        centre_color = centre_shade;
        if (centre_shade >= 0x100) {
            centre_color = 0xFF;
        }
    }
    if (arc_shade < 0) {
        arc_color = 0;
    } else {
        arc_color = arc_shade;
        if (arc_shade >= 0x100) {
            arc_color = 0xFF;
        }
    }
    GFX_AddDitheredDrawMode(1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    phase = 0;
    i     = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = centre_x;
        prim->y0 = centre_y;
        prim->x1 = centre_x + ((radius * rcos((u16)phase)) >> 12);
        prim->y1 = centre_y + ((radius * rsin((u16)phase)) >> 12);
        phase += 0x80;
        prim->x2 = centre_x + ((radius * rcos((u16)phase)) >> 12);
        prim->y2 = centre_y + ((radius * rsin((u16)phase)) >> 12);
        prim->r0 = centre_color;
        prim->g0 = centre_color;
        prim->b0 = centre_color;
        prim->r1 = arc_color;
        prim->g1 = arc_color;
        prim->b1 = arc_color;
        prim->r2 = arc_color;
        prim->g2 = arc_color;
        prim->b2 = arc_color;
        GFX_AddPrim(1, sizeof(POLY_G3));
        i += 1;
    } while (i < 0x20);
}
