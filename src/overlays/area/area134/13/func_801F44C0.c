#include "area134_13.h"

MATCH void func_801F44C0(void) {
    Actor* work;
    u8     timer;

    timer = --g_Task->timer;
    if (timer == 0) {
        Actor_Clear();
    } else {
        work = g_Task;
        /* FAKE: the retail update spans mixed-width actor fields. */
        FIELD(u16, work, 0x20) -= 512;
        FIELD(s32, work, 0x24) -= 0x100000;
        func_801F4B6C();
    }
}
