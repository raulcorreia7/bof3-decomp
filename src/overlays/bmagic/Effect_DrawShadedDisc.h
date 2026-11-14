/* Draws a disc of 64 shaded triangles around the effect cell, its radius the effect param byte 0x0B and its shade the timer times 4. */
/* func_801EF7E0 (magic053), func_801EF814 (magic226) */
MATCH void Effect_DrawShadedDisc(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->param.unk_0B;
    D_1F800000.view.effect.params[5] = g_Task->timer << 2;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        setRGB2(prim, LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[5]));
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}
