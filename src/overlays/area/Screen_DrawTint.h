/* Draws a semi-transparent tile over the whole screen in the colour of the task's tint. One definition shared by
 * the area overlays; every change here must verify every member. */
/* Shared by area085, area108, area149, area175, area191 and scena13; scena13 has a second copy at
 * 801F7484 that names itself through SCREEN_TINT_FUNC. */
#ifndef SCREEN_TINT_FUNC
#define SCREEN_TINT_FUNC Screen_DrawTint
#endif
MATCH void SCREEN_TINT_FUNC(void) {
    TILE* tile;
    u8    blue;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, SCREEN_TINT_TPAGE, NULL);
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

#undef SCREEN_TINT_FUNC
