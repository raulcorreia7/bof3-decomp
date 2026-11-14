/* The ring fan of magic055 (func_801EF7B0) and magic091 (func_801EF7B0): eight semi-transparent G3 segments
 * around the effect cell, each under its own draw mode, the radius twice the effect timer plus 32 and the centre
 * colour the timer times 10. Every change must verify both member images. */
MATCH void func_801EF7B0(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 2 + 32;
    for (i = 0; i < 8; i++) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]),
               g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]), g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]),
               g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]));
        setRGB0(prim, g_Task->unk_09 * 10, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
