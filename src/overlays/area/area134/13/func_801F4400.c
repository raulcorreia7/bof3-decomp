#include "area134_13.h"

MATCH void func_801F4400(void) {
    Actor* work;
    s32    limit;
    u8     timer;

    work = TASK(Actor);
    work->unk_1C += 0x1000000;
    limit = work->vz + 0x8000000;
    if (limit < work->unk_1C) {
        work->unk_1C = limit;
    }
    FIELD(u16, g_Task, 0x20u) -= 0x200;
    func_801F4B6C();
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (timer == 0) {
        TASK(Actor)->timer = 16;
        TASK(Actor)->header.mode++;
    }
}
