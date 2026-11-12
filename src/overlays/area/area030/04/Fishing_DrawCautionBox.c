#include "area030_04.h"

/* Draws the AREA030 selector box. */
/* func_801E19CC */
MATCH void Fishing_DrawCautionBox(s32 x, s32 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, ((y + 1)), 179, 66, 0x80, g_WindowStyle);
    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(37, 1, sx, sy);
    for (i = 0; i < 15; i++) {
        Fishing_DrawSprite(38, 1, (sx + 32 + i * 8), sy);
    }
    Fishing_DrawSprite(39, 1, (sx + 152), sy);
    Fishing_DrawSprite(40, 1, (sx + 176), sy);
    Fishing_DrawWindowFill(sx, (sy + 24), 40, 0);
    Fishing_DrawWindowFill((sx + 176), (sy + 24), 40, 1);
    Fishing_DrawSprite(48, 1, sx, (sy + 64));
    for (i = 0; i < 21; i++) {
        Fishing_DrawSprite(49, 1, (sx + 8 + i * 8), (sy + 64));
    }
    Fishing_DrawSprite(50, 1, (sx + 176), (sy + 64));
    UI_DrawText((sx + 62), (sy + 6), 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_CAUTION));
    UI_DrawText((sx + 6), (sy + 25), 0, 255, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_TOO_MANY_ITEMS));
}
