/* Fills a menu panel and draws its tiled border. */
/* func_801D6470 (bate), func_801DBF18 (shop), func_801D7418 (shisu), func_801DF410 (start) */
MATCH void Menu_DrawFilledPanel(s16 x, s16 y, s16 width, s32 height) {
    u8 i;

    UI_WindowDraw((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, (u8)width * 8 + 45, (u8)height * 8 + 24, 0, g_WindowStyle);
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 832, 256) & HALF_MASK);

    UI_SpriteDraw(x, y, 0, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < (u8)width; i++) {
        UI_SpriteDraw(x + (i + 4) * 8, y, 1, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(x + ((u8)width + 4) * 8, y, 2, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(x + ((u8)width + 6) * 8, y, 3, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < (u8)width + 5; i++) {
        UI_SpriteDraw(x + (i + 1) * 8, y + ((u8)height + 3) * 8, 6, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < (u8)height; i++) {
        UI_SpriteDraw(x, y + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
        UI_SpriteDraw(x + ((u8)width + 6) * 8, y + (i + 3) * 8, 8, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(x, y + ((u8)height + 3) * 8, 5, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(x + ((u8)width + 6) * 8, y + ((u8)height + 3) * 8, 7, UI_SPRITE_ALT_PAGE);
}
