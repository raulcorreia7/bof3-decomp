#include "game_00.h"

/* Callee entry at 0x801C71C4 writes one word through out and
 * returns the incoming pointer (caller ignores the result). */

MATCH s32 func_801C7064(s32 x, s32 y, s32 reach, s32 height) {
    u16 halves[2];
    s32 step;
    s32 prev;
    u32 count;
    s32 base_x;
    s32 base_y;

    step  = ((reach & 0xFF) + 1) << 14;
    prev  = step;
    count = 0;
    do {
        s32 saved;

        base_x = x + prev;
        base_y = y + step;
        func_801C71C4(halves, base_x, base_y, Area_SampleHeight(base_x, base_y) << 0x10);
        if (halves[0] >= 320) {
            return 0;
        }
        if (halves[1] < 240) {
            saved = prev;
            prev  = step;
            step  = -saved;
            count += 1;
        } else {
            return 0;
        }
    } while ((count & 0xFF) < 4);
    base_x = x + prev;
    base_y = y + step;
    func_801C71C4(halves, base_x, base_y, Area_SampleHeight(base_x, base_y) << 0x10);
    return ((s16)halves[1] - (height & 0xFF)) >= 8;
}
