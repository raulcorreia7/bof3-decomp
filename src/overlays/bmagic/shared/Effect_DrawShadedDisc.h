/* Draws a disc of 64 shaded triangles around the effect cell, its radius the effect param byte 0x0B and its shade the timer times 4. */
/* func_801EF7E0 (magic053), func_801EF814 (magic226) */
MATCH void Effect_DrawShadedDisc(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->timer << 2;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 64; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB1(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}
