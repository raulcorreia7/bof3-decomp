#include "area042_13.h"

MATCH void func_801F2D48(void) {
    func_801F2E78(&g_Task->vx, &g_Task->unk_18);
    func_801F2DC4();
    if (SYS_TestFlag(g_SceneEventFlags, 11) == 0) {
        g_Task->header.mode = 0;
    }
}
