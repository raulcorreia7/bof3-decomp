#include "game_00.h"

MATCH void func_801C1E88(s32 key, s32* counter) {
    s32 step;
    s32 outer;
    s32 total;
    s32 inner;
    s32 next;
    s32 val;

    total = 0;
    outer = 0;
    val   = 4;
    key &= BYTE_MASK;
    step = 0;
    do {
        if ((g_FairyRooms[step] == val) && (g_FairyRooms[1 + step] == key)) {
            next  = outer + 1;
            inner = 0;
            do {
                if ((((u8*)g_FairyJobs)[inner] != 0) && (((u8*)g_FairyJobs)[inner + 1] == next)) {
                    total += 1;
                }
                inner += 8;
            } while (inner < 480);
        }
        outer += 1;
        step += 8;
    } while (outer < 8);
    if (!(total & BYTE_MASK)) {
        *counter += 1;
    }
}
