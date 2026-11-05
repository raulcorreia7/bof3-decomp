#include "area042_13.h"

MATCH void func_801F3988(void) {
    g_Task->unk_09 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[g_Task->x.part.integer])) {
        func_801F3D18(3);
        g_Task->step = 3;
    } else {
        func_801F3D18(0);
        g_Task->step = 1;
    }
}
