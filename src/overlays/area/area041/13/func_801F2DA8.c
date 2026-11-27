#include "area041_13.h"

MATCH void func_801F2DA8(void) {
    if (SYS_TestFlag(g_SceneFlagRows[D_801F42CC[SELF(Actor)->param.unk_0B]], D_801F42D0[SELF(Actor)->param.unk_0B])) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step++;
    }
    func_801F2EFC();
    func_801F3064();
}
