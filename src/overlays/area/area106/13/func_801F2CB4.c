#include "area106_13.h"

MATCH void func_801F2CB4(void) {
    Actor* work;

    if (g_AreaSceneMode == 1) {
        g_Task->timer = 0;
        work          = g_Task;
        work->header.step++;
        func_801F2F38(0, 0);
    }
}
