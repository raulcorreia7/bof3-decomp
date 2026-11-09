#include "area117_13.h"

MATCH u8 func_801F4110(u8 member) {
    s32 x;
    s32 y;
    s32 i;
    s32 off;

    i   = 0;
    off = 0;
    x   = g_Game.members[member].pos.x.fixed;
    y   = g_Game.members[member].pos.y.fixed;
    do {
        if (x >= (D_801F558C[off] << 16) && (D_801F558C[off + 2] << 16) >= x && y >= (D_801F558C[off + 1] << 16) &&
            (D_801F558C[off + 3] << 16) >= y) {
            return i;
        }
        i++;
        off += 6;
    } while (i <= 0);
    return 0xFF;
}
