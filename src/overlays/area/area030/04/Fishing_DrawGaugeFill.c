#include "area030_04.h"

/* Queues the two AREA030 menu icon gouraud quads. */

/* func_801D1B88 */
MATCH void Fishing_DrawGaugeFill(s16 quad_x, s16 quad_y, s16 quad_width, u8 corner_shade) {
    POLY_G4* primitive;

    primitive = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(primitive);
    setXY0(primitive, quad_x, quad_y);
    primitive->x1 = quad_x + quad_width;
    primitive->y1 = quad_y;
    setRGB0(primitive, 0, 0, 0);
    setRGB1(primitive, 0, 0, 0);
    setRGB2(primitive, 0, 128, 0);
    setRGB3(primitive, 0, 128, 0);
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    primitive->y2 = primitive->y0 + 4;
    primitive->y3 = primitive->y2;
    GFX_AddPrim(corner_shade & BYTE_MASK, sizeof(POLY_G4));

    primitive = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(primitive);
    primitive->x1 = quad_x + quad_width;
    setXY0(primitive, quad_x, quad_y + 4);
    primitive->y1 = quad_y + 4;
    setRGB0(primitive, 0, 128, 0);
    setRGB1(primitive, 0, 128, 0);
    setRGB2(primitive, 0, 0, 0);
    setRGB3(primitive, 0, 0, 0);
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    primitive->y2 = primitive->y0 + 4;
    primitive->y3 = primitive->y2;
    GFX_AddPrim(corner_shade & BYTE_MASK, sizeof(POLY_G4));
}
