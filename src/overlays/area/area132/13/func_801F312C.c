#include "area132_13.h"

MATCH void func_801F312C(void) {
    Actor* work;
    s32    limit;
    u8     timer;

    work = g_Task;
    work->unk_1C += 0x1000000;
    limit = work->vz + 0x8000000;
    if (limit < work->unk_1C) {
        work->unk_1C = limit;
    }
    FIELD(u16, g_Task, 0x20u) -= 0x200;
    func_801F3268();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer = 16;
        g_Task->header.mode++;
    }
}
