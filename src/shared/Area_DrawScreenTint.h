/* Draws a semi-transparent tile over the whole screen in the colour of the task's tint, queued on the prim layer
 * `layer` under the draw-mode texture page `tpage`. Shared by the area overlays and scena13. */
static inline void Screen_DrawTintLayer(u32 layer, s32 tpage) {
    TILE* tile;
    u8    blue;

    GFX_AddDitheredDrawMode(layer, tpage);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    tile->r0 = g_Task->tint.bytes.unk_5D;
    tile->g0 = g_Task->tint.bytes.unk_5E;
    blue     = g_Task->tint.bytes.unk_5F;
    tile->w  = SCREEN_WIDTH;
    tile->x0 = 0;
    tile->y0 = 0;
    tile->h  = SCREEN_HEIGHT;
    tile->b0 = blue;
    SetSemiTrans(tile, 1);
    SetShadeTex(tile, 0);
    GFX_AddPrim(layer, sizeof(TILE));
}
