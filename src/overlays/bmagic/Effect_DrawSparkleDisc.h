/* Draws the disc of the current sparkle as eight POLY_G3 wedges around its screen point. */
/* Effect_DrawSparkleDisc (magic070, magic071, magic072, magic073, magic074, magic162, magic168) */
MATCH void Effect_DrawSparkleDisc(void) {
    POLY_G3* prim;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[2] = EFFECT_SPARKLE_TASK->unk_06 + (rand() & 3);
    D_1F800000.view.effect.params[0] = EFFECT_SPARKLE_TASK->unk_20;
    D_1F800000.view.effect.params[1] = EFFECT_SPARKLE_TASK->unk_22;
    D_1F800000.view.effect.params[4] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][0] * EFFECT_SPARKLE_TASK->timer_05;
    D_1F800000.view.effect.params[5] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][1] * EFFECT_SPARKLE_TASK->timer_05;
    D_1F800000.view.effect.params[6] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][2] * EFFECT_SPARKLE_TASK->timer_05;
    D_1F800000.view.effect.params[7] = EFFECT_SPARKLE_TASK->timer_05;
    for (i = 0; i < 8; i++) {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = D_1F800000.view.effect.params[0];
        prim->y0 = D_1F800000.view.effect.params[1];
        prim->x1 = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[2]);
        prim->y1 = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[2]);
        prim->x2 = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[2]);
        prim->y2 = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[2]);
        prim->r0 = D_1F800000.view.effect.params[4];
        prim->g0 = D_1F800000.view.effect.params[5];
        prim->b0 = D_1F800000.view.effect.params[6];
        prim->r1 = D_1F800000.view.effect.params[7];
        prim->g1 = D_1F800000.view.effect.params[7];
        prim->b1 = D_1F800000.view.effect.params[7];
        prim->r2 = D_1F800000.view.effect.params[7];
        prim->g2 = D_1F800000.view.effect.params[7];
        prim->b2 = D_1F800000.view.effect.params[7];
        Area_AddCellPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
