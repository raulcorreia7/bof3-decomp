#include "boss013_16.h"

MATCH void func_800C1DF4(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->header.flags & 0x80) {
        work->header.step++;
    } else {
        work->pos.x.fixed += 0x8000;
        func_8014D978();
        func_8014D978();
    }
}
