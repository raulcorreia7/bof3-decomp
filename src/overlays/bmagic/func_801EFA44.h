/* Draws the four rays of the sparkle as LINE_G3 wedges around the effect point: each wedge runs from the centre
 * in the scratch halfwords D_1F800000/2 through the half-radius point to the point at the frame angle and the
 * radius, its corners white at the centre and coloured from the scratch colour halfwords D_1F800000.view.effect.params[4]-[6]; the effect
 * point takes a DR_MODE cell and a 32-byte cell prim. */
/* func_801EFA44 (magic070), func_801EFA44 (magic071), func_801EFA44 (magic072) */
MATCH void func_801EFA44(u16 angle, u16 radius) {
    LINE_G3* prim;
    s32      tpage;
    s32      i;

    D_1F800000.view.effect.params[0] = LOHU(D_801F17B4->unk_20);
    D_1F800000.view.effect.params[1] = D_801F17B4->unk_22;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, sizeof(DR_MODE));

    D_1F800000.view.effect.params[4] = D_801F17B4->timer_05 * 6;
    D_1F800000.view.effect.params[5] = D_801F17B4->timer_05 * 6;
    D_1F800000.view.effect.params[6] = D_801F17B4->timer_05 * 6;

    for (i = angle; i < angle + 0x20; i += 8) {
        prim = (LINE_G3*)g_GfxPrimCursor;
        SetLineG3(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[3] = (i & 0x1F) << 7;
        prim->x0                         = LOHU(D_1F800000.view.effect.params[0]);
        prim->y0                         = LOHU(D_1F800000.view.effect.params[1]);
        prim->x1                         = LOHU(D_1F800000.view.effect.params[0]) + FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), radius >> 1);
        prim->y1                         = LOHU(D_1F800000.view.effect.params[1]) + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), radius >> 1);
        prim->x2                         = LOHU(D_1F800000.view.effect.params[0]) + FIXED_MUL(rcos(D_1F800000.view.effect.params[3]), radius);
        prim->y2                         = LOHU(D_1F800000.view.effect.params[1]) + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), radius);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, LOHU(D_1F800000.view.effect.params[4]), LOHU(D_1F800000.view.effect.params[5]), LOHU(D_1F800000.view.effect.params[6]));
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, BMAGIC_RAY_CELL_SIZE);
    }
}
