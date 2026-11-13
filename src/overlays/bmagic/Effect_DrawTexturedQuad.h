/* Draws the effect's textured quad as four diamond corners around its screen point. */
/* Effect_DrawTexturedQuad (magic145, magic146) */
MATCH void Effect_DrawTexturedQuad(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_09 << 1;
    D_1F800000.view.effect.params[2] = g_Task->timer << 3;
    prim                             = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0    = g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.view.effect.params[0]);
    prim->y0    = g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.view.effect.params[0]);
    prim->x1    = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    prim->y1    = g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    prim->x2    = g_Task->unk_2E.half + FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    prim->y2    = g_Task->unk_30.half + FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    prim->x3    = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    prim->y3    = g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    prim->tpage = GetTPage(0, 2, 832, 256);
    prim->clut  = GetClut(32, 506);
    prim->u0    = 128;
    prim->v0    = 32;
    prim->u1    = 160;
    prim->v1    = 32;
    prim->u2    = 128;
    prim->v2    = 64;
    prim->u3    = 160;
    prim->v3    = 64;
    prim->r0    = D_1F800000.view.effect.params[2];
    prim->g0    = D_1F800000.view.effect.params[2];
    prim->b0    = D_1F800000.view.effect.params[2];
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}
