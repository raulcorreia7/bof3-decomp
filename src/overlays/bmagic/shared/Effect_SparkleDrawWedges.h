/* Draws the four wedges of a sparkle from its point through the half radius to the radius, white at the centre and far points and tinted at the half radius. Every change must verify all member images. */
/* func_801EFA44 (magic070), func_801EFA44 (magic071), func_801EFA44 (magic072), func_801EFE2C (magic073), func_801EFE18 (magic074), func_801EFA40 (magic162), func_801EFA40 (magic168) */
MATCH void Effect_SparkleDrawWedges(u16 angle, u16 radius) {
    LINE_G3* prim;
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
        prim = (LINE_G3*)g_GfxPrimCursor;
        SetLineG3(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.ray.angle = (i & 0x1F) << 7;
        setXY0(prim, LOHU(g_ScratchPad.cells.ray.x), LOHU(g_ScratchPad.cells.ray.y));
        prim->x1 = LOHU(g_ScratchPad.cells.ray.x) + FIXED_MUL(rcos(g_ScratchPad.cells.ray.angle), radius >> 1);
        prim->y1 = LOHU(g_ScratchPad.cells.ray.y) + FIXED_MUL(rsin(g_ScratchPad.cells.ray.angle), radius >> 1);
        prim->x2 = LOHU(g_ScratchPad.cells.ray.x) + FIXED_MUL(rcos(g_ScratchPad.cells.ray.angle), radius);
        prim->y2 = LOHU(g_ScratchPad.cells.ray.y) + FIXED_MUL(rsin(g_ScratchPad.cells.ray.angle), radius);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, LOHU(g_ScratchPad.cells.ray.shade.r), LOHU(g_ScratchPad.cells.ray.shade.g), LOHU(g_ScratchPad.cells.ray.shade.b));
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(EFFECT_SPARKLE_TASK->pos.x.fixed, EFFECT_SPARKLE_TASK->pos.y.fixed, 2, BMAGIC_RAY_CELL_SIZE);
    }
}
