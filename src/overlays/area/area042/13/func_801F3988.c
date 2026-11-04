#include "area042_13.h"

MATCH void func_801F3988(void) {
    g_SpadWork->unk_09 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, D_801F532C[g_SpadWork->x.part.integer])) {
        func_801F3D18(3);
        g_SpadWork->state_02 = 3;
    } else {
        func_801F3D18(0);
        g_SpadWork->state_02 = 1;
    }
}
