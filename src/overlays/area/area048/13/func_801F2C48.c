#include "area048_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (!SYS_TestFlag(g_SceneEventFlags, 13)) {
        work = SELF(Actor);
        step = 2;
    } else {
        work = SELF(Actor);
        step = 1;
    }
    work->header.mode = step;
    work              = SELF(Actor);
    work->pos.z.fixed = TO_COORD(256);
}
