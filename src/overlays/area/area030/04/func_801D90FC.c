#include "area030_04.h"

/* Draws the area status panel and its borders at (x, y + 2). */
MATCH void func_801D90FC(s32 x, s16 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, (y + 2), 139, 20, 0, g_WindowStyle);
    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(63, 1, sx, sy);
    Fishing_DrawSprite(64, 1, (sx + 8), sy);
    Fishing_DrawSprite(65, 1, (sx + 16), sy);
    for (i = 0; i < 8; i++) {
        Fishing_DrawSprite(38, 1, (sx + 40 + i * 8), sy);
    }
    Fishing_DrawSprite(66, 1, (sx + 104), sy);
    Fishing_DrawSprite(67, 1, (sx + 120), sy);
    Fishing_DrawSprite(68, 1, (sx + 128), sy);
    Fishing_DrawWindowFill(sx, (sy + 24), 120, 0);
    Fishing_DrawSprite(70, 1, (sx + 128), (sy + 24));
    Fishing_DrawWindowFill((sx + 128), (sy + 40), 104, 4);
    Fishing_DrawSprite(42, 1, sx, (sy + 144));
    for (i = 0; i < 15; i++) {
        Fishing_DrawSprite(43, 1, (sx + 8 + i * 8), (sy + 144));
    }
    Fishing_DrawSprite(69, 1, (sx + 128), (sy + 136));
}
