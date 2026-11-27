#include "area139_13.h"

MATCH void func_801F2C48(void) {
    Actor* work;
    u8     step;

    if (g_GameCellType == 2 && !SYS_TestFlag(g_SceneEventFlags, 92)) {
        work = SELF(Actor);
        step = 1;
    } else if (g_GameCellType == 3 && SYS_TestFlag(g_SceneEventFlags, 93)) {
        work = SELF(Actor);
        step = 2;
    } else {
        work = SELF(Actor);
        step = 3;
    }
    work->header.mode = step;
}
