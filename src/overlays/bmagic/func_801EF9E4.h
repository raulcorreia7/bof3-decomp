/* The triangle fan of magic055 (func_801EF9E4) and magic091 (func_801EF9E4): eight segments of
 * a semi-transparent G3 ring around the effect centre, its radius a fixed 0x120 and its first corner
 * colour the effect timer times 12. Every change must verify both member images. */
MATCH void func_801EF9E4(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 2, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.cells.halves[0] = 0x120;
    D_1F800000.cells.halves[5] = g_Task->timer * 12;
    D_1F800014[2].vx           = FIXED_MUL(rsin(0), D_1F800000.cells.halves[0]);
    D_1F800014[2].vy           = FIXED_MUL(rcos(0), D_1F800000.cells.halves[0]);
    D_1F800014[2].vz           = 0;
    D_1F800014[1].vz           = 0;
    D_1F800014[0].vz           = 0;

    for (i = 1; i <= 8; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 9), D_1F800000.cells.halves[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 9), D_1F800000.cells.halves[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.cells.halves[5], D_1F800000.cells.halves[5], D_1F800000.cells.halves[5]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}
