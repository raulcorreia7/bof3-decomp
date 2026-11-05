#include "area030_04.h"

/* PsyQ SetPolyF4; the SDK map omits this entry, so the address name is kept. */

/* Draws the AREA030 panel's bottom caption bar: a Gouraud panel plus
 * a 16x16 mode sprite, then a flat quad built from the two caption columns. The
 * bar top tracks the world height helper unless the countdown gate is off, and
 * the second icon slides up while the count is still running. */
MATCH void func_801D195C(s16 panel_x, s16 panel_y) {
    POLY_F4* primitive;
    s16      x;
    s16      y;
    s16      base;

    func_801D1744((s16)(panel_x + 0x58), (s16)(panel_y + 8), 4);

    if (g_ActorSlots[0].mode == 0) {
        y = panel_y;
    } else {
        y = panel_y - Area_SampleHeight(g_ActorSlots[0].x.fixed, g_ActorSlots[0].y.fixed) / 32;
    }
    base = panel_y;
    CLAMP_MIN(y, base);
    x = (s16)(panel_x + 0x59);
    func_801D1818(x, y, 4);

    primitive = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(primitive);
    primitive->x0 = x;
    primitive->x1 = (s16)(panel_x + 105);
    primitive->y0 = (s16)(y + 16);
    primitive->y1 = (s16)(y + 16);
    primitive->y2 = (s16)(base + 40);
    primitive->y3 = (s16)(base + 40);
    setRGB0(primitive, 72, 32, 0);
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    GFX_AddPrim(4, 0x18);

    if (g_ActorSlots[0].mode == 4) {
        y = 0xB4;
        if (g_ActorSlots[0].z.part.integer <= 0) {
            y = 0xB4 - g_ActorSlots[0].z.part.integer / 32;
        }
        func_801D18CC((s16)(panel_x + 0x69), y, 2);
    }
}
