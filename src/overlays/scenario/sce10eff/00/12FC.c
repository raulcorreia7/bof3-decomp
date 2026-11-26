#include "sce10eff_00.h"

MATCH void func_801D1EFC(void) {
    SceneBandEffect* work;

    work = SELF(SceneBandEffect);
    if (work->band < 16) {
        work->band += 2;
    } else {
        work->timer = 60;
        work        = SELF(SceneBandEffect);
        work->step_index++;
    }
}
