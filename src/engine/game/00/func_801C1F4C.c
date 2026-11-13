#include "game_00.h"

MATCH void func_801C1F4C(s32 key) {
    u8* counter;
    s32 step;
    s32 outer;
    s32 next;
    s32 total;
    s32 inner;

    outer = 0;
    key &= BYTE_MASK;
    counter = &D_801448D8;
    step    = 0;
    do {
        total = 0;
        if ((g_FairyRooms[step] == key) && (*(&D_801457AB + step) != 0)) {
            next  = outer + 1;
            inner = 0;
            do {
                if ((((u8*)g_FairyJobs)[inner] != 0) && (((u8*)g_FairyJobs)[inner + 1] == next)) {
                    total += 1;
                }
                inner += 8;
            } while (inner < 480);
            if (!(total & BYTE_MASK)) {
                *(s32*)(counter + 0xED4) = *(s32*)((u8*)&D_801457AC + step) + 1;
            }
        }
        counter += 8;
        outer += 1;
        step += 8;
    } while (outer < 8);
}
