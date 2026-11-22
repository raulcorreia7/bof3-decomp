#include "area197_13.h"

MATCH void func_801F2E74(SparkParticle* spark) {
    POLY_F3* poly;
    FAKE_STACK_PADS(u8, 48); /* FAKE: retail frame reserves 48 bytes no statement uses. */

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
    Area_CellAddPrim(spark->pos.vx, spark->pos.vy, -2, sizeof(DR_MODE));
    poly = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(poly);
    SetSemiTrans(poly, 1);
    Camera_ProjectPoint(&spark->pos.vx, POLY_XY(poly, 0));
    poly->x1 = poly->x0 + D_801F4328[spark->frame].dx1;
    poly->y1 = poly->y0 + D_801F4328[spark->frame].dy1;
    poly->x2 = poly->x0 + D_801F4328[spark->frame].dx2;
    poly->y2 = poly->y0 + D_801F4328[spark->frame].dy2;
    setRGB0(poly, 0, spark->header.shade, spark->header.shade);
    Area_CellAddPrim(spark->pos.vx, spark->pos.vy, -2, sizeof(POLY_F3));
}
