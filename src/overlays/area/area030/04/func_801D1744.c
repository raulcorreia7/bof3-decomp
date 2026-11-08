#include "area030_04.h"

/* Builds the AREA030 Gouraud quad panel: two 16-pixel-wide columns
 * whose right column repeats the left column's edge, then appends the 0x24-byte
 * primitive with the caller's semi-transparency mode. */
MATCH void func_801D1744(s16 panel_x, s16 panel_y, u8 column_shade) {
    POLY_G4* primitive;

    primitive = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(primitive);
    primitive->x0 = panel_x;
    primitive->x1 = panel_x + 16;
    primitive->y0 = panel_y;
    primitive->y1 = panel_y;
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    primitive->y2 = primitive->y0 + 32;
    primitive->y3 = primitive->y2;
    setRGB0(primitive, 100, 100, 128);
    setRGB1(primitive, 100, 100, 128);
    setRGB2(primitive, 0, 0, 80);
    setRGB3(primitive, 0, 0, 80);
    GFX_AddPrim(column_shade, sizeof(POLY_G4));
}
