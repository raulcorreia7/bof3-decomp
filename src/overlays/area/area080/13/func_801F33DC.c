#include "area080_13.h"

MATCH void func_801F33DC(AreaRing* ring) {
    POLY_F3* poly;
    u8       shade;
    u8       i;
    u8       j;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x3C0, 0));
    for (i = 0; i < AREA_RING_POINTS; i++) {
        j = (i + 1) & (AREA_RING_POINTS - 1);
        if (func_801AFF90((Point2D*)&ring->screen_base, (Point2D*)&ring->screen[i], (Point2D*)&ring->screen[j]) > 0) {
            poly = (POLY_F3*)g_GfxPrimCursor;
            SetPolyF3(poly);
            SetSemiTrans(poly, 1);
            poly->x0 = ring->screen_base.vx;
            poly->y0 = ring->screen_base.vy;
            poly->x1 = ring->screen[i].vx;
            poly->y1 = ring->screen[i].vy;
            poly->x2 = ring->screen[j].vx;
            poly->y2 = ring->screen[j].vy;
            shade    = ring->unk_22;
            poly->b0 = shade;
            poly->g0 = shade;
            poly->r0 = shade;
            GFX_AddPrim(1, sizeof(POLY_F3));
        }
    }
}
