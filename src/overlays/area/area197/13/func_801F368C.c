#include "area197_13.h"

MATCH void func_801F368C(void) {
    if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 14)) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
    func_801F3768(0x80, 0);
}
