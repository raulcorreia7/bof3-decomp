#include "area132_13.h"

MATCH void func_801F312C(void) {
    Actor* work;
    s32    limit;
    u8     timer;

    work = SELF(Actor);
    work->unk_1C += 0x1000000;
    limit = work->vz + 0x8000000;
    if (limit < work->unk_1C) {
        work->unk_1C = limit;
    }
    FIELD(u16, g_Self, 0x20u) -= 0x200;
    func_801F3268();
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (timer == 0) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode++;
    }
}
