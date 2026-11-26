/* Draws the ring of eight Gouraud triangles around the effect position, shaded by the work bytes 0x5D to 0x5F. */
/* magic076, magic169 */
MATCH void BMagic_DrawRingTriangles(void) {
    POLY_G3* prim;
    s16      i;
    s16      x;
    s16      y;

    x                            = SELF(PartyMember)->screen_x.value;
    y                            = SELF(PartyMember)->screen_y.value;
    g_ScratchPad.cells.halves[0] = 8;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 12;
    g_ScratchPad.cells.halves[4] = (s8)SELF(PartyMember)->unk_5D * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5E * SELF(PartyMember)->unk_09;
    g_ScratchPad.cells.halves[6] = (s8)SELF(PartyMember)->unk_5F * SELF(PartyMember)->unk_09;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, x, y, x + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]),
               x + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        setRGB2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6]);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
