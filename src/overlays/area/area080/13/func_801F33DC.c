#include "area080_13.h"

MATCH void func_801F33DC(AreaRing* ring) {
    POLY_F3* poly;
    u8       shade;
    u8       i;
    u8       j;

    GFX_AddDitheredDrawMode(1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    for (i = 0; i < AREA_RING_POINTS; i++) {
        j = (i + 1) & (AREA_RING_POINTS - 1);
        if (func_801AFF90((Pos2*)&ring->screen_base, (Pos2*)&ring->screen[i], (Pos2*)&ring->screen[j]) > 0) {
            poly = (POLY_F3*)g_GfxPrimCursor;
            SetPolyF3(poly);
            SetSemiTrans(poly, 1);
            setXY3(poly, ring->screen_base.vx, ring->screen_base.vy, ring->screen[i].vx, ring->screen[i].vy, ring->screen[j].vx, ring->screen[j].vy);
            shade    = ring->unk_22;
            poly->b0 = shade;
            poly->g0 = shade;
            poly->r0 = shade;
            GFX_AddPrim(1, sizeof(POLY_F3));
        }
    }
}
