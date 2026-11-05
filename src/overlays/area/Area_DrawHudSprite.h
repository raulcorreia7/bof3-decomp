/* Draws one sprite at (x, y) from the four-byte (w, h, u0, v0) cell that sprite_id selects in AREA_HUD_SPRITE_CELLS.
 * One definition shared by the area overlays; every change here must verify every member. */
MATCH void Area_DrawHudSprite(s32 x, s32 y, u32 sprite_id) {
    SPRT* sprt;
    s32   tpage;
    s32   idx;

    tpage = getTPage(1, 0, 768, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(1, 0xC);

    sprt = GfxBeginSprite(x, y, WORLD_SPRITE_CLUT);

    idx      = (sprite_id & BYTE_MASK) << 2;
    sprt->w  = AREA_HUD_SPRITE_CELLS[idx];
    sprt->h  = AREA_HUD_SPRITE_CELLS[idx + 1];
    sprt->u0 = AREA_HUD_SPRITE_CELLS[idx + 2];
    sprt->v0 = AREA_HUD_SPRITE_CELLS[idx + 3];

    GFX_AddPrim(1, 0x14);
}
