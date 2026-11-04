#include "area068_13.h"

MATCH void func_801F3074(void) {
    Actor* work;
    u8     step;

    if (D_801F4E08 == 0) {
        work = g_SpadWork;
        step = 0x16;
    } else {
        work       = g_SpadWork;
        D_801F4E0C = 0;
        step       = 0xB;
    }
    work->unk_01 = step;
}
