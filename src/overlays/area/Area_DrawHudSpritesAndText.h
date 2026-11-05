/* When any area draw mode is set, draws HUD sprites 4 and 5 side by side
 * and the value text at their corner.
 */
/* func_801F40FC (area065), func_801F40C4 (area045) */
MATCH void Area_DrawHudSpritesAndText(s16 x, s16 y) {
    if ((g_AreaDrawFlags & (AREA_DRAW_SORTED_RECORDS | AREA_DRAW_NEGATIVE_DEPTH | AREA_DRAW_APPEND_ACTOR_PRIMITIVES |
                            AREA_DRAW_APPEND_AREA_PRIMITIVES)) == 0) {
        return;
    }
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x, y, 4);
    ((void (*)(s16, s16, u32))Area_DrawHudSprite)(x + 0x80, y, 5);
    UI_DrawText(x + 4, y + 4, 0, 0xFF, (u8*)((u16)(*(u16*)((u8*)&D_80010008 - 4)) + 0x80010000u));
}
