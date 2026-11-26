/* Draws the four rays of a sparkle from its point out to the radius, tinted at the centre and white at the far end. Every change must verify all member images. */
/* func_801EF810 (magic070), func_801EF810 (magic071), func_801EF810 (magic072), func_801EFBF8 (magic073), func_801EFBE4 (magic074), func_801EF80C (magic162), func_801EF80C (magic168) */
MATCH void Effect_SparkleDrawRays(u16 angle, u16 radius) {
    LINE_G2* prim;
    s32      tpage;
    s32      i;

    g_ScratchPad.cells.ray.x = LOHU(EFFECT_SPARKLE_TASK->unk_20);
    g_ScratchPad.cells.ray.y = EFFECT_SPARKLE_TASK->unk_22;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, sizeof(DR_MODE));

    g_ScratchPad.cells.ray.shade.r = EFFECT_SPARKLE_TASK->timer_05 * 6;
    g_ScratchPad.cells.ray.shade.g = EFFECT_SPARKLE_TASK->timer_05 * 6;
    g_ScratchPad.cells.ray.shade.b = EFFECT_SPARKLE_TASK->timer_05 * 6;

    for (i = angle; i < angle + 0x20; i += 8) {
        prim = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.ray.angle = (i & 0x1F) << 7;
        setXY0(prim, LOHU(g_ScratchPad.cells.ray.x), LOHU(g_ScratchPad.cells.ray.y));
        prim->x1 = LOHU(g_ScratchPad.cells.ray.x) + FIXED_MUL(rcos(g_ScratchPad.cells.ray.angle), radius);
        prim->y1 = LOHU(g_ScratchPad.cells.ray.y) + FIXED_MUL(rsin(g_ScratchPad.cells.ray.angle), radius);
        setRGB0(prim, LOHU(g_ScratchPad.cells.ray.shade.r), LOHU(g_ScratchPad.cells.ray.shade.g), LOHU(g_ScratchPad.cells.ray.shade.b));
        setRGB1(prim, 1, 1, 1);
        Area_CellAddPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, BMAGIC_RAY_CELL_SIZE);
    }
}
