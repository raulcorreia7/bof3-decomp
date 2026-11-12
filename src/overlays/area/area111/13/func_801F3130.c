#include "area111_13.h"

MATCH void func_801F3130(void) {
    g_Task->screen_y = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 40) != 0) {
        Actor_Clear();
        return;
    }
    g_Task->header.step++;
    func_801F3244();
}
