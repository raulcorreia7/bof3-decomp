#include "area068_13.h"

MATCH void func_801F2F24(void) {
    Actor* work;
    u8     step;

    if (g_InputPressed == 0x10) {
        D_801F4E04++;
    }
    D_801F4E0C++;
    if (D_801F4E0C >= 0x1C) {
        work = g_SpadWork;
        step = 0x16;
    } else {
        work = g_SpadWork;
        step = 4;
    }
    work->unk_01 = step;
}
