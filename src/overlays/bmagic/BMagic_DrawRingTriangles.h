/* Draws the ring of eight Gouraud triangles around the effect position, shaded by the work bytes 0x5D to 0x5F. */
/* magic076, magic169 */
MATCH void BMagic_DrawRingTriangles(void) {
    POLY_G3* prim;
    s16      i;
    s16      x;
    s16      y;

    x                          = g_Task->unk_2E.half;
    y                          = g_Task->unk_30.half;
    D_1F800000.cells.halves[0] = 8;
    D_1F800000.cells.halves[3] = g_Task->unk_09 * 12;
    D_1F800000.cells.halves[4] = (s8)g_Task->unk_5D * g_Task->unk_09;
    D_1F800000.cells.halves[5] = (s8)g_Task->unk_5E * g_Task->unk_09;
    D_1F800000.cells.halves[6] = (s8)g_Task->unk_5F * g_Task->unk_09;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, x, y, x + FIXED_MUL(rsin(i << 9), D_1F800000.cells.halves[0]), y + FIXED_MUL(rcos(i << 9), D_1F800000.cells.halves[0]),
               x + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.cells.halves[0]), y + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.cells.halves[0]));
        setRGB0(prim, D_1F800000.cells.halves[3], D_1F800000.cells.halves[3], D_1F800000.cells.halves[3]);
        setRGB1(prim, D_1F800000.cells.halves[4], D_1F800000.cells.halves[5], D_1F800000.cells.halves[6]);
        setRGB2(prim, D_1F800000.cells.halves[4], D_1F800000.cells.halves[5], D_1F800000.cells.halves[6]);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
