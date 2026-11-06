#include "area135_14.h"

MATCH void func_801F3ABC(void) {
    if (SYS_TestFlag(&g_SceneEventFlags, 0x2A)) {
        g_Task->z.fixed     = -0x180;
        g_Task->header.step = 3;
    } else {
        g_Task->z.fixed = -0x90;
        g_Task->header.step++;
    }
    func_801F3CA8();
}
