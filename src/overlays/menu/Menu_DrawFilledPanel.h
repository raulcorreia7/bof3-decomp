/* Fills a menu panel and draws its tiled border. One definition shared by the
 * shop and Bate overlays; every change here must verify every member. */
/* func_801D6470 (bate), func_801DBF18 (shop), func_801D7418 (shisu), func_801DF410 (start) */
MATCH void Menu_DrawFilledPanel(s16 x, s16 y, s16 width, s32 height) {
    u8 i;

    UI_DrawWindow((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, (u8)width * 8 + 45, (u8)height * 8 + 24, 0, g_WindowStyle);
    GFX_AddDrawMode(GetTPage(0, 0, 832, 256) & HALF_MASK);

    UI_DrawSprite(x, y, 0, 1);
    for (i = 0; i < (u8)width; i++) {
        UI_DrawSprite(x + (i + 4) * 8, y, 1, 1);
    }
    UI_DrawSprite(x + ((u8)width + 4) * 8, y, 2, 1);
    UI_DrawSprite(x + ((u8)width + 6) * 8, y, 3, 1);
    for (i = 0; i < (u8)width + 5; i++) {
        UI_DrawSprite(x + (i + 1) * 8, y + ((u8)height + 3) * 8, 6, 1);
    }
    for (i = 0; i < (u8)height; i++) {
        UI_DrawSprite(x, y + (i + 3) * 8, 4, 1);
        UI_DrawSprite(x + ((u8)width + 6) * 8, y + (i + 3) * 8, 8, 1);
    }
    UI_DrawSprite(x, y + ((u8)height + 3) * 8, 5, 1);
    UI_DrawSprite(x + ((u8)width + 6) * 8, y + ((u8)height + 3) * 8, 7, 1);
}
