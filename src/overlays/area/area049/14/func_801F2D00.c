#include "area049_14.h"

MATCH s32 func_801F2D00(u8 member) {
    s32 i = 0;
    s32 j = 0;
    s32 x = g_Game.members[member].pos.x.fixed;
    s32 y = g_Game.members[member].pos.y.fixed;

    while (i < 7) {
        if (x >= ((s32)D_801F5C08[j + 0] << 16) && x <= ((s32)D_801F5C08[j + 2] << 16) &&
            y >= ((s32)D_801F5C08[j + 1] << 16) && y <= ((s32)D_801F5C08[j + 3] << 16)) {
            return i & 0xFF;
        }
        i++;
        j += 6;
    }

    return 0xFF;
}
