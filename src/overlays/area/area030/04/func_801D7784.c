#include "area030_04.h"

/* Draws the 0x17-cell work list at (list_x, list_y) with its 0x78-wide
 * frames, the 0x17-cell gauge row at list_y + 0x90, and the three-cell tail,
 * then closes the frame. */
MATCH void func_801D7784(u16 list_x, u16 list_y) {
    s32 i;
    s32 offset;
    s16 x;
    s16 y;

    Fishing_SetDrawMode(9, 1);
    Fishing_DrawSprite(37, 1, list_x, list_y);

    for (i = 0; i < 23; i++) {
        offset = i * 8 + 32;
        Fishing_DrawSprite(38, 1, (list_x + offset), list_y);
    }

    Fishing_DrawSprite(39, 1, (list_x + 216), list_y);

    x = list_x + 240;
    Fishing_DrawSprite(40, 1, x, list_y);

    y = list_y + 24;
    Fishing_DrawWindowFill(list_x, y, 120, 0);
    Fishing_DrawWindowFill(x, y, 120, 1);

    Fishing_DrawSprite(42, 1, list_x, (list_y + 144));

    i      = 0;
    offset = 8;
    do {
        Fishing_DrawSprite(43, 1, (list_x + offset), (list_y + 144));
        i += 1;
        offset += 8;
    } while (i < 23);

    Fishing_DrawSprite(44, 1, (list_x + 192), (list_y + 144));

    i      = 0;
    offset = 200;
    do {
        Fishing_DrawSprite(45, 1, (list_x + offset), (list_y + 144));
        i += 1;
        offset += 8;
    } while (i < 3);

    Fishing_DrawSprite(46, 1, (list_x + 224), (list_y + 144));
    Fishing_DrawSprite(47, 1, (list_x + 231), (list_y + 144));
}
