#include "area030_04.h"

/* PsyQ SetPolyF4; the SDK map omits this entry, so the address name is kept. */

/* Draws the AREA030 panel's bottom caption bar: a Gouraud panel plus
 * a 16x16 mode sprite, then a flat quad built from the two caption columns. The
 * bar top tracks the world height helper unless the countdown gate is off, and
 * the second icon slides up while the count is still running. */
/* func_801D195C */
MATCH void Fishing_DrawDepthGauge(s16 panel_x, s16 panel_y) {
    POLY_F4* primitive;
    s16      x;
    s16      y;
    s16      base;

    func_801D1744((panel_x + 88), (panel_y + 8), 4);

    if (g_SpawnedActors[0].header.mode == 0) {
        y = panel_y;
    } else {
        y = panel_y - Area_SampleHeight(g_SpawnedActors[0].pos.x.fixed, g_SpawnedActors[0].pos.y.fixed) / 32;
    }
    base = panel_y;
    CLAMP_MIN(y, base);
    x = (panel_x + 89);
    func_801D1818(x, y, 4);

    primitive = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(primitive);
    primitive->x1 = (panel_x + 105);
    setXY0(primitive, x, (y + 16));
    primitive->y1 = (y + 16);
    primitive->y2 = (base + 40);
    primitive->y3 = (base + 40);
    setRGB0(primitive, 72, 32, 0);
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    GFX_AddPrim(4, sizeof(POLY_F4));

    if (g_SpawnedActors[0].header.mode == 4) {
        y = 180;
        if (COORD_INT(g_SpawnedActors[0].pos.z) <= 0) {
            y = 180 - COORD_INT(g_SpawnedActors[0].pos.z) / 32;
        }
        Fishing_DrawIcon((panel_x + 105), y, 2);
    }
}
