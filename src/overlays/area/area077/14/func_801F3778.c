#include "area077_14.h"

MATCH void func_801F3778(u8 count, Pos2* current, RECT* rect) {
    u8 shade;
    u8 i;

    shade = 0x40;
    for (i = 0; i < count - 1; i++) {
        if (current[1].vx >= rect->x && current[1].vx < rect->x + rect->w) {
            if (current[0].vx >= current[1].vx) {
                func_801F3898(current[0], current[1], shade);
            } else {
                func_801F3B48(&current[1], shade);
            }
        }
        if (shade != 0) {
            shade -= 2;
        }
        current++;
    }
}
