/* Draws a semi-transparent tile over the whole screen in the colour of the task's tint. One definition shared by
 * the area overlays; every change here must verify every member. */
/* func_801F2ED8 (area085), func_801F3438 (area175) */
MATCH void Screen_DrawTint(void) {
    TILE* tile;
    u8    blue;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 0x3C0, 0), NULL);
    GFX_AddPrim(SCREEN_TINT_LAYER, 0xCU);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    tile->r0 = g_Task->tint.bytes.unk_5D;
    tile->g0 = g_Task->tint.bytes.unk_5E;
    blue     = g_Task->tint.bytes.unk_5F;
    tile->w  = 0x140;
    tile->x0 = 0;
    tile->y0 = 0;
    tile->h  = 0xF0;
    tile->b0 = blue;
    SetSemiTrans(tile, 1);
    SetShadeTex(tile, 0);
    GFX_AddPrim(SCREEN_TINT_LAYER, 0x10U);
}
