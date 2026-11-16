#include "area080_13.h"

/* Fill the screen above and below the ring with its band shade and draw the
 * band between each pair of ring points. */
MATCH void func_801F31A0(AreaRing* ring) {
    POLY_F4* poly;
    TILE*    tile;
    u8       shade;
    s16      top;
    s16      bottom;
    u8       i;
    u8       j;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));

    top    = 0;
    bottom = 0xF0;
    i      = 0;
    do {
        j = (i + 1) & (AREA_RING_POINTS - 1);
        if (top < ring->screen[i].vy) {
            top = ring->screen[i].vy;
        }
        if (ring->screen[i].vy < bottom) {
            bottom = ring->screen[i].vy;
        }

        poly = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(poly);
        SetSemiTrans(poly, 1);
        poly->x0 = ring->screen[i].vx;
        poly->y0 = poly->y1 = ring->screen[i].vy;
        poly->x2            = ring->screen[j].vx;
        poly->y2 = poly->y3 = ring->screen[j].vy;
        if (ring->screen_center.vx < (ring->screen[i].vx + ring->screen[j].vx) >> 1) {
            poly->x3 = 0x140;
            poly->x1 = 0x140;
        } else {
            poly->x3 = 0;
            poly->x1 = 0;
        }
        shade    = ring->unk_23;
        poly->b0 = shade;
        poly->g0 = shade;
        poly->r0 = shade;
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F4));
        i++;
    } while (i < AREA_RING_POINTS);

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->x0 = 0;
    tile->y0 = 0;
    tile->w  = 0x140;
    tile->h  = bottom;
    shade    = ring->unk_23;
    tile->b0 = shade;
    tile->g0 = shade;
    tile->r0 = shade;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->x0 = 0;
    tile->y0 = top;
    tile->w  = 0x140;
    tile->h  = 0xF0 - top;
    shade    = ring->unk_23;
    tile->b0 = shade;
    tile->g0 = shade;
    tile->r0 = shade;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}
