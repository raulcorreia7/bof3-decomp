/* Runs the step handler header.step (byte 0x02) selects, draws the effect's two translucent ring
 * layers and projects the battle range. Every change must verify every member image. */
/* func_801EF8EC (magic076), func_801EF8A4 (magic169) */
MATCH void Effect_DrawRings(void) {
    BMagicSteps handlers = BMagic_EffectSteps;
    s32         tpage;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        BMagic_DrawRingTriangles();
        BMagic_DrawRingQuads();
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
}
