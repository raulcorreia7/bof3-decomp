#include "area172_13.h"

/* The grey variant of the shared spawn slot fan: grey corner shades, and it joins order list 1. */
MATCH void Area_DrawSpawnSlot(AreaSpawnSlot* slot) {
    u16      size[2];
    u16      scale[2];
    DVECTOR  screen;
    POLY_G3* primitive;
    s16      radius;
    u16      angle;
    u8       core;
    u8       rim;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    size[0] = slot->radius;
    Game_ProjectWorldPoint(&slot->pos, size, scale);
    Area_ProjectPoint(&slot->pos.x.fixed, &screen);
    radius = scale[0] + (g_FrameCount & 1);
    angle  = 0;
    do {
        primitive = GFX_BeginPolyG3(1);
        setXY2(primitive, screen.vx, screen.vy, screen.vx + ((radius * rcos((u16)angle)) >> 0xC), screen.vy + ((radius * rsin((u16)angle)) >> 0xC));
        angle += 128;
        primitive->x2 = screen.vx + ((radius * rcos((u16)angle)) >> 0xC);
        primitive->y2 = screen.vy + ((radius * rsin((u16)angle)) >> 0xC);
        core          = slot->core_shade;
        primitive->b0 = core;
        primitive->g0 = core;
        primitive->r0 = core;
        rim           = slot->rim_shade;
        primitive->b2 = rim;
        primitive->g2 = rim;
        primitive->r2 = rim;
        primitive->b1 = rim;
        primitive->g1 = rim;
        primitive->r1 = rim;
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
    } while ((u16)angle < ONE);
}
