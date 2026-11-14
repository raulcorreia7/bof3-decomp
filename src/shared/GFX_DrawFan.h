/* Draws a fan of eight semi-transparent triangles from a point, the centre corner in the given shade. */
/* GFX_DrawFan (scena07, scena08, area088) */
MATCH void GFX_DrawFan(Point2s* point, s16 radius, u16 angle, u8 colour) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = point->x;
        prim->y0 = point->y;
        prim->x1 = point->x + FIXED_MUL(radius, rcos(angle));
        prim->y1 = point->y + FIXED_MUL(radius, rsin(angle));
        angle += 0x100;
        prim->x2 = point->x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = point->y + FIXED_MUL(radius, rsin(angle));
        prim->b0 = colour;
        prim->g0 = colour;
        prim->r0 = colour;
        prim->b2 = 0;
        prim->g2 = 0;
        prim->r2 = 0;
        prim->b1 = 0;
        prim->g1 = 0;
        prim->r1 = 0;
        GFX_AddPrim(1, sizeof(POLY_G3));
    } while (i < 8);
}
