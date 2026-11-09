/* Draws the HUD banner at (x, y) when any draw flag is set: the left and right
 * banner sprites (4 and 5, 0x80 apart) and the title line whose offset sits at
 * the head of the main executable's text bank. One definition shared by the
 * area overlays; every change here must verify every member image. */
/* FAKE: the call-through casts pass the s16 arguments of the retail call site. needs: type for Area_DrawHudSprite */
MATCH void Area_DrawHudBanner(s16 x, s16 y) {
    if ((g_AreaDrawFlags & (AREA_DRAW_SORTED_RECORDS | AREA_DRAW_NEGATIVE_DEPTH | AREA_DRAW_APPEND_ACTOR_PRIMITIVES |
                            AREA_DRAW_APPEND_AREA_PRIMITIVES)) == 0) {
        return;
    }
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x, y, 4);
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x + 0x80, y, 5);
    UI_DrawText(x + 4, y + 4, 0, 0xFF, (u8*)(MEM(u16, 0x80010000u) + 0x80010000u));
}
