/* Draws one spawn slot as a 32-segment shaded fan at its projected position: the frame count
 * flickers the radius, and the slot's two shades fill the centre and the rim. */
/* func_801F53BC (area098), func_801F3F30 (area188) */
MATCH void Area_DrawSpawnSlot(AreaSpawnSlot* slot) {
    POLY_G3* prim;
    s16      radius;
    u16      angle;
    u8       core;
    u8       rim;
    Point2D  size;
    UPoint2D projected;
    DVECTOR  screen;

    GFX_AddDitheredDrawMode(2, GetTPage(0, 1, 0x3C0, 0));

    size.x = slot->radius_14;
    func_801AFFD8(&slot->pos, &size, &projected);
    Area_ProjectPoint((s32*)&slot->pos, &screen);

    radius = projected.x + (g_FrameCount & 1);
    angle  = 0;
    do {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = screen.vx;
        prim->y0 = screen.vy;
        prim->x1 = screen.vx + FIXED_MUL(radius, rcos(angle));
        prim->y1 = screen.vy + FIXED_MUL(radius, rsin(angle));
        angle += ONE / 32;
        prim->x2 = screen.vx + FIXED_MUL(radius, rcos(angle));
        prim->y2 = screen.vy + FIXED_MUL(radius, rsin(angle));
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
    } while ((u16)angle < ONE);
}
