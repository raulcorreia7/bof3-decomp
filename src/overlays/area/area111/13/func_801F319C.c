#include "area111_13.h"

MATCH void func_801F319C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x28)) {
        g_Task->header.step++;
    }
    func_801F3244();
}
