/* Draws the effect's textured quad as four diamond corners around its screen point. */
/* Effect_DrawTexturedQuad (magic145, magic146) */
MATCH void Effect_DrawTexturedQuad(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256), 0);
    Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = g_Task->unk_09 << 1;
    g_ScratchPad.cells.halves[2] = g_Task->timer << 3;
    prim                         = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0    = g_Task->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]);
    prim->y0    = g_Task->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]);
    prim->x1    = g_Task->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]);
    prim->y1    = g_Task->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]);
    prim->x2    = g_Task->screen_x.value + FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]);
    prim->y2    = g_Task->screen_y.value + FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]);
    prim->x3    = g_Task->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]);
    prim->y3    = g_Task->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 832, 256);
    prim->clut  = GetClut(32, 506);
    setUV4(prim, 128, 32, 160, 32, 128, 64, 160, 64);
    setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
