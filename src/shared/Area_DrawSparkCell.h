/* The spark cell draw func_801F387C (area082) and func_801F7A24 (scena01) share: project the spark, queue a 1x1
 * semi-transparent cell at its screen position, shade it by one random bit and add it to the area cell list at its
 * world position. Every change must keep both members matching. */
MATCH void Area_DrawSparkCell(AreaSpark* spark) {
    DVECTOR screen;
    s32     unused[4]; /* FAKE: pads the frame to retail size. */
    TILE_1* tile;
    u8      shade;

    Area_ProjectPoint(&spark->pos.x, &screen);
    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 0);
    setXY0(tile, screen.vx, screen.vy);
    shade    = -RANDOM_MASK(1);
    tile->b0 = shade;
    tile->g0 = shade;
    tile->r0 = shade;
    Area_AddCellPrim(spark->pos.x, spark->pos.y, 0, sizeof(TILE_1));
}
