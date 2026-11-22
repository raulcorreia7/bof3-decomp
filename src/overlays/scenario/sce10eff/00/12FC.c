#include "sce10eff_00.h"

MATCH void func_801D1EFC(void) {
    SceneBandEffect* work;

    work = TASK(SceneBandEffect);
    if (work->band < 16) {
        work->band += 2;
    } else {
        work->timer = 60;
        work        = TASK(SceneBandEffect);
        work->step_index++;
    }
}
