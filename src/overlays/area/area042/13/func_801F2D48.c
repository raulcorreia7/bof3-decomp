#include "area042_13.h"

MATCH void func_801F2D48(void) {
    func_801F2E78(&TASK(Actor)->vx, &TASK(Actor)->unk_18);
    func_801F2DC4();
    if (SYS_TestFlag(g_SceneEventFlags, 11) == 0) {
        TASK(Actor)->header.mode = 0;
    }
}
