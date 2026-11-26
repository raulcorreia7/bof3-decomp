#include "area111_13.h"

MATCH void func_801F319C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 40)) {
        SELF(Actor)->header.step++;
    }
    func_801F3244();
}
