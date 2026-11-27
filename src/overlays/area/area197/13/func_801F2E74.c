#include "area197_13.h"

MATCH void func_801F2E74(SparkParticle* spark) {
    POLY_F3* poly;
    /* FAKE: retail reserves 16 more frame bytes than the two cell positions take; no statement uses them. */
    FAKE_STACK_PADS(u8, 16);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
    {
        Coord cell_x = {spark->pos.vx};
        Coord cell_y = {spark->pos.vy};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, -2, sizeof(DR_MODE));
    }
    poly = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(poly);
    SetSemiTrans(poly, 1);
    Camera_ProjectPoint(&spark->pos.vx, POLY_XY(poly, 0));
    poly->x1 = poly->x0 + D_801F4328[spark->frame].dx1;
    poly->y1 = poly->y0 + D_801F4328[spark->frame].dy1;
    poly->x2 = poly->x0 + D_801F4328[spark->frame].dx2;
    poly->y2 = poly->y0 + D_801F4328[spark->frame].dy2;
    setRGB0(poly, 0, spark->header.shade, spark->header.shade);
    {
        Coord cell_x = {spark->pos.vx};
        Coord cell_y = {spark->pos.vy};

        Area_CellAddPrim(cell_x.fixed, cell_y.fixed, -2, sizeof(POLY_F3));
    }
}
