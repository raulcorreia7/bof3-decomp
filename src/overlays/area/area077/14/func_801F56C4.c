#include "area077_14.h"
#include "area/spad.h"

MATCH void func_801F56C4(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 7) != 0) {
        g_Task->header.step++;
    }
}
