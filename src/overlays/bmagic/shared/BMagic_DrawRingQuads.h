/* Draws the ring of eight Gouraud quads around the effect position, shaded by the work bytes 0x5D to 0x5F. */
/* magic076, magic169 */
MATCH void BMagic_DrawRingQuads(void) {
    POLY_G4* prim;
    s16      i;
    s16      x;
    s16      y;

    x                            = SELF(PartyMember)->screen_x.value;
    y                            = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[0] = 8;
    g_ScratchPad.cells.halves[1] = 20;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->unk_09;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[1]), y + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[1]));
        prim->x2 = x + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]);
        prim->y2 = y + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]);
        prim->x1 = x + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[1]);
        prim->y1 = y + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[1]);
        prim->x3 = x + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]);
        prim->y3 = y + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB3(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}
