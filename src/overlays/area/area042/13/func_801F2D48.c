#include "area042_13.h"

MATCH void func_801F2D48(void) {
    func_801F2E78(&SELF(Actor)->vx, &SELF(Actor)->unk_18);
    func_801F2DC4();
    if (SYS_TestFlag(g_SceneEventFlags, 11) == 0) {
        SELF(Actor)->header.mode = 0;
    }
}
