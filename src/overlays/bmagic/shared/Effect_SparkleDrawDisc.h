/* Draws the disc of the current sparkle as eight POLY_G3 wedges around its screen point. */
/* Effect_SparkleDrawDisc (magic070, magic071, magic072, magic073, magic074, magic162, magic168) */
MATCH void Effect_SparkleDrawDisc(void) {
    POLY_G3* prim;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[2] = EFFECT_SPARKLE_TASK->unk_06 + (rand() & 3);
    g_ScratchPad.cells.halves[0] = EFFECT_SPARKLE_TASK->unk_20;
    g_ScratchPad.cells.halves[1] = EFFECT_SPARKLE_TASK->unk_22;
    g_ScratchPad.cells.halves[4] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][0] * EFFECT_SPARKLE_TASK->timer_05;
    g_ScratchPad.cells.halves[5] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][1] * EFFECT_SPARKLE_TASK->timer_05;
    g_ScratchPad.cells.halves[6] = EFFECT_SPARKLE_COLORS[EFFECT_SPARKLE_TASK->unk_04][EFFECT_SPARKLE_TASK->unk_03][2] * EFFECT_SPARKLE_TASK->timer_05;
    g_ScratchPad.cells.halves[7] = EFFECT_SPARKLE_TASK->timer_05;
    for (i = 0; i < 8; i++) {
        prim = GFX_BeginPolyG3(1);
        setXY3(prim, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[2]),
               g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0] + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[2]),
               g_ScratchPad.cells.halves[1] + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[2]));
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB1(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        setRGB2(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        Area_CellAddPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
