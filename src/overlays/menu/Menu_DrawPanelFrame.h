/* func_801D78A8 (bate), func_801D8850 (shisu), func_801DD350 (shop), func_801E0848 (start) */
MATCH void Menu_DrawPanelFrame(s16 x, s16 y, s32 width, s32 height) {
    s16 px;
    s16 py;
    u8  i;
    u8  w;
    u8  h;

    /* The callers pass the extents as s32; the panel uses their low byte. */
    w = width;
    h = height;

    GFX_AddDrawMode(GetTPage(0, 0, 896, 256) & 0xFFFF);

    for (i = 0; i < w; i++) {
        px = x + ((i + 1) * 8);
        UI_DrawSprite(px, y, 0x29, 0);
        UI_DrawSprite(px, y + ((h + 1) * 8), 0x2E, 0);
    }
    for (i = 0; i < h; i++) {
        py = y + ((i + 1) * 8);
        UI_DrawSprite(x, py, 0x2B, 0);
        UI_DrawSprite(x + ((w + 1) * 8), py, 0x2C, 0);
    }
    UI_DrawSprite(x, y, 0x28, 0);
    UI_DrawSprite(x + ((w + 1) * 8), y, 0x2A, 0);
    UI_DrawSprite(x, y + ((h + 1) * 8), 0x2D, 0);
    UI_DrawSprite(x + ((w + 1) * 8), y + ((h + 1) * 8), 0x2F, 0);
}
