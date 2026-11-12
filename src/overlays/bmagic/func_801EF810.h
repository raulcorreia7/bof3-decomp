/* Draws the four rays of the sparkle around the effect point: each ray is a LINE_G2 from the centre in the
 * scratch halfwords D_1F800000/2 out to the rcos and rsin point at the frame angle plus its step, coloured from
 * the scratch colour halfwords D_1F800000_HALF[4]-[6], and the effect point takes a DR_MODE cell and a 32-byte cell prim. */
/* func_801EF810 (magic070), func_801EF810 (magic071), func_801EF810 (magic072) */
MATCH void func_801EF810(u16 angle, u16 radius) {
    LINE_G2* prim;
    s32      tpage;
    s32      i;

    D_1F800000_HALF[0] = LOHU(D_801F17B4->unk_20);
    D_1F800000_HALF[1] = D_801F17B4->unk_22;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, sizeof(DR_MODE));

    D_1F800000_HALF[4] = D_801F17B4->timer_05 * 6;
    D_1F800000_HALF[5] = D_801F17B4->timer_05 * 6;
    D_1F800000_HALF[6] = D_801F17B4->timer_05 * 6;

    for (i = angle; i < angle + 0x20; i += 8) {
        prim = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(prim);
        SetSemiTrans(prim, 1);
        D_1F800000_HALF[3] = (i & 0x1F) << 7;
        prim->x0           = LOHU(D_1F800000_HALF[0]);
        prim->y0           = LOHU(D_1F800000_HALF[1]);
        prim->x1           = LOHU(D_1F800000_HALF[0]) + FIXED_MUL(rcos(D_1F800000_HALF[3]), radius);
        prim->y1           = LOHU(D_1F800000_HALF[1]) + FIXED_MUL(rsin(D_1F800000_HALF[3]), radius);
        setRGB0(prim, LOHU(D_1F800000_HALF[4]), LOHU(D_1F800000_HALF[5]), LOHU(D_1F800000_HALF[6]));
        setRGB1(prim, 1, 1, 1);
        Area_AddCellPrim(D_801F17B4->pos.x.fixed, D_801F17B4->pos.y.fixed, 2, 32);
    }
}
