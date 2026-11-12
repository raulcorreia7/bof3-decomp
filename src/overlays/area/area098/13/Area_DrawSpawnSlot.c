#include "area098_13.h"

/* Draw one spawn slot as the 32-segment shaded fan at its projected position. */
MATCH void Area_DrawSpawnSlot(AreaSpawnSlot* slot) {
    POLY_G3* prim;
    s16      radius;
    u16      angle;
    u8       core;
    u8       rim;
    Point2D  size;
    u16      projected[2];
    DVECTOR  screen;

    GFX_AddDitheredDrawMode(2, (u16)GetTPage(0, 1, 0x3C0, 0));

    size.x = slot->radius_14;
    func_801AFFD8(&slot->pos, &size, projected);
    Area_ProjectPoint((s32*)&slot->pos, &screen);

    radius = projected[0] + (g_FrameCount & 1);
    angle  = 0;
    do {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = screen.vx;
        prim->y0 = screen.vy;
        prim->x1 = screen.vx + ((radius * rcos(angle)) >> 0x0C);
        prim->y1 = screen.vy + ((radius * rsin(angle)) >> 0x0C);
        angle += 0x80;
        prim->x2 = screen.vx + ((radius * rcos(angle)) >> 0x0C);
        prim->y2 = screen.vy + ((radius * rsin(angle)) >> 0x0C);
        core     = slot->core_shade_16;
        prim->b0 = 0;
        prim->g0 = core;
        prim->r0 = core;
        rim      = slot->rim_shade_17;
        prim->b2 = 0;
        prim->b1 = 0;
        prim->g2 = rim;
        prim->r2 = rim;
        prim->g1 = rim;
        prim->r1 = rim;
        GFX_AddPrim(2, sizeof(POLY_G3));
    } while ((u16)angle < 0x1000);
}
