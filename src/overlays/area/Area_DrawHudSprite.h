/* Draws one sprite at (x, y) from the four-byte (w, h, u0, v0) cell that sprite_id selects in AREA_HUD_SPRITE_CELLS.
 * One definition shared by the area overlays; every change here must verify every member. */
MATCH void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id) {
    SPRT* sprt;
    s32   tpage;
    s32   index;

    tpage = getTPage(1, 0, 768, 256);
    GFX_AddDrawMode(tpage);

    sprt = GfxBeginSprite(x, y, WORLD_SPRITE_CLUT);

    index    = (sprite_id & BYTE_MASK) << 2;
    sprt->w  = AREA_HUD_SPRITE_CELLS[index];
    sprt->h  = AREA_HUD_SPRITE_CELLS[index + 1];
    sprt->u0 = AREA_HUD_SPRITE_CELLS[index + 2];
    sprt->v0 = AREA_HUD_SPRITE_CELLS[index + 3];

    GFX_AddPrim(1, 0x14);
}
