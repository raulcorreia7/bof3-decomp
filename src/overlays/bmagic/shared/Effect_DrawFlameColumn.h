/* Draws the flame column: rows 4 to 31, each four textured quads whose half widths follow a sine of the row; the outer pair fades to black. Every change must verify every member. */
/* func_801EF818 (magic144), func_801EFB04 (magic092) */
MATCH void Effect_DrawFlameColumn(void) {
    POLY_GT4* prim;
    s32       i;
    s32       step;
    s32       tpage;

    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->screen_y.value;
    step                         = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 3;

    for (i = 4; i < 32; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        g_ScratchPad.cells.halves[4] = FIXED_MUL(rsin((i + 1) << 6), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[5] = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[7] = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 * 3 + (rand() & 0xF);
        g_ScratchPad.cells.halves[6] = FIXED_MUL(rsin((i + 1) << 6), g_ScratchPad.cells.halves[1]);

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[4];
        prim->x1 = g_ScratchPad.cells.halves[2];
        prim->x2 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[5];
        prim->x3 = g_ScratchPad.cells.halves[2];
        /* setXY4 would read each row offset twice. */
        prim->y0 = prim->y1 = g_ScratchPad.cells.halves[3] - (i - 3) * step;
        prim->y2 = prim->y3 = g_ScratchPad.cells.halves[3] - (i - 4) * step;
        setRGB0(prim, 0xA0, 0x20, 0x20);
        setRGB1(prim, 0x80, 0x80, 0x20);
        setRGB2(prim, 0xA0, 0x20, 0x20);
        setRGB3(prim, 0x80, 0x80, 0x20);
        prim->clut  = GetClut(0, 506);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
        setUV4(prim, 0x80 - g_ScratchPad.cells.halves[4], (i - 3) * 6 + 0x20 + step, 0x80, (i - 3) * 6 + 0x20 + step, 0x80 - g_ScratchPad.cells.halves[5], (i - 4) * 6 + 0x20 + step, 0x80,
               (i - 4) * 6 + 0x20 + step);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = g_ScratchPad.cells.halves[2];
        prim->x1 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[4];
        prim->x2 = g_ScratchPad.cells.halves[2];
        prim->x3 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[5];
        prim->y0 = prim->y1 = g_ScratchPad.cells.halves[3] - (i - 3) * step;
        prim->y2 = prim->y3 = g_ScratchPad.cells.halves[3] - (i - 4) * step;
        setRGB0(prim, 0x80, 0x80, 0x20);
        setRGB1(prim, 0xA0, 0x20, 0x20);
        setRGB2(prim, 0x80, 0x80, 0x20);
        setRGB3(prim, 0xA0, 0x20, 0x20);
        prim->clut  = GetClut(0, 506);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
        setUV4(prim, 0x80, (i - 3) * 6 + 0x20 + step, g_ScratchPad.cells.halves[4] + 0x80, (i - 3) * 6 + 0x20 + step, 0x80, (i - 4) * 6 + 0x20 + step, g_ScratchPad.cells.halves[5] + 0x80,
               (i - 4) * 6 + 0x20 + step);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[6];
        prim->x1 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[4];
        prim->x2 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[7];
        prim->x3 = g_ScratchPad.cells.halves[2] - g_ScratchPad.cells.halves[5];
        prim->y0 = prim->y1 = g_ScratchPad.cells.halves[3] - (i - 3) * step;
        prim->y2 = prim->y3 = g_ScratchPad.cells.halves[3] - (i - 4) * step;
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 0x80, 0x20, 0x20);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 0x80, 0x20, 0x20);
        prim->clut  = GetClut(0, 506);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
        setUV4(prim, 0x80 - g_ScratchPad.cells.halves[6], (i - 3) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[4], (i - 3) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[7],
               (i - 4) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[5], (i - 4) * 6 + 0x20 + step * 2);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));

        prim = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[4];
        prim->x1 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[6];
        prim->x2 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[5];
        prim->x3 = g_ScratchPad.cells.halves[2] + g_ScratchPad.cells.halves[7];
        prim->y0 = prim->y1 = g_ScratchPad.cells.halves[3] - (i - 3) * step;
        prim->y2 = prim->y3 = g_ScratchPad.cells.halves[3] - (i - 4) * step;
        setRGB0(prim, 0x80, 0x20, 0x20);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 0x80, 0x20, 0x20);
        setRGB3(prim, 1, 1, 1);
        prim->clut  = GetClut(0, 506);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
        setUV4(prim, 0x80 - g_ScratchPad.cells.halves[4], (i - 3) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[6], (i - 3) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[5],
               (i - 4) * 6 + 0x20 + step * 2, 0x80 - g_ScratchPad.cells.halves[7], (i - 4) * 6 + 0x20 + step * 2);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
    }
}
