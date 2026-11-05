#include "sce10eff_00.h"

MATCH void func_801D1EFC(void) {
    SceneBandEffect* work;

    work = g_Task;
    if (work->band < 16) {
        work->band += 2;
    } else {
        work->timer = 60;
        work        = g_Task;
        work->step_index++;
    }
}
