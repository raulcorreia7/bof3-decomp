#include "area030_04.h"

/* Draws the 0x17-cell work list at (list_x, list_y) with its 0x78-wide
 * frames, the 0x17-cell gauge row at list_y + 0x90, and the three-cell tail,
 * then closes the frame. */
MATCH void func_801D7784(u16 list_x, u16 list_y) {
    s32 i;
    s32 offset;
    s16 x;
    s16 y;

    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, list_x, list_y);

    for (i = 0; i < 23; i++) {
        offset = i * 8 + 32;
        func_801E0DCC(0x26, 1, (list_x + offset), list_y);
    }

    func_801E0DCC(0x27, 1, (list_x + 216), list_y);

    x = list_x + 240;
    func_801E0DCC(0x28, 1, x, list_y);

    y = list_y + 24;
    func_801D799C(list_x, y, 120, 0);
    func_801D799C(x, y, 120, 1);

    func_801E0DCC(0x2A, 1, list_x, (list_y + 144));

    i      = 0;
    offset = 8;
    do {
        func_801E0DCC(0x2B, 1, (list_x + offset), (list_y + 144));
        i += 1;
        offset += 8;
    } while (i < 23);

    func_801E0DCC(0x2C, 1, (list_x + 192), (list_y + 144));

    i      = 0;
    offset = 200;
    do {
        func_801E0DCC(0x2D, 1, (list_x + offset), (list_y + 144));
        i += 1;
        offset += 8;
    } while (i < 3);

    func_801E0DCC(0x2E, 1, (list_x + 224), (list_y + 144));
    func_801E0DCC(0x2F, 1, (list_x + 231), (list_y + 144));
}
