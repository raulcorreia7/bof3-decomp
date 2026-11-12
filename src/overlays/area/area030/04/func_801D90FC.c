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
    Fishing_DrawSprite(0x3F, 1, sx, sy);
    Fishing_DrawSprite(0x40, 1, (sx + 8), sy);
    Fishing_DrawSprite(0x41, 1, (sx + 16), sy);
    for (i = 0; i < 8; i++) {
        Fishing_DrawSprite(0x26, 1, (sx + 40 + i * 8), sy);
    }
    Fishing_DrawSprite(0x42, 1, (sx + 104), sy);
    Fishing_DrawSprite(0x43, 1, (sx + 120), sy);
    Fishing_DrawSprite(0x44, 1, (sx + 128), sy);
    Fishing_DrawWindowFill(sx, (sy + 24), 120, 0);
    Fishing_DrawSprite(0x46, 1, (sx + 128), (sy + 24));
    Fishing_DrawWindowFill((sx + 128), (sy + 40), 104, 4);
    Fishing_DrawSprite(0x2A, 1, sx, (sy + 144));
    for (i = 0; i < 15; i++) {
        Fishing_DrawSprite(0x2B, 1, (sx + 8 + i * 8), (sy + 144));
    }
    Fishing_DrawSprite(0x45, 1, (sx + 128), (sy + 136));
}
