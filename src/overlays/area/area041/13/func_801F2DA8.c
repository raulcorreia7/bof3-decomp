#include "area041_13.h"

MATCH void func_801F2DA8(void) {
    if (SYS_TestFlag(g_SceneFlagRows[D_801F42CC[TASK(Actor)->param.unk_0B]], D_801F42D0[TASK(Actor)->param.unk_0B])) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step++;
    }
    func_801F2EFC();
    func_801F3064();
}
