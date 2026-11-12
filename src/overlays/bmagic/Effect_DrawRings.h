/* Runs the step handler header.step (byte 0x02) selects, draws the effect's two translucent ring
 * layers and projects the battle range. Every change must verify every member image. */
/* func_801EF8EC (magic076), func_801EF8A4 (magic169) */
MATCH void Effect_DrawRings(void) {
    BMagicStepHandlers handlers = BMagic_EffectSteps;
    s32                tpage;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        BMagic_DrawRingTriangles();
        BMagic_DrawRingQuads();
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
}
