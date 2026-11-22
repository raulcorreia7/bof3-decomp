#include "area106_13.h"

MATCH void func_801F2CB4(void) {
    Actor* work;

    if (g_AreaSceneMode == 1) {
        TASK(Actor)->timer = 0;
        work               = TASK(Actor);
        work->header.step++;
        func_801F2F38(0, 0);
    }
}
