#include "area111_13.h"

MATCH void func_801F3130(void) {
    g_Task->unk_30 = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 0x28) != 0) {
        Actor_Clear();
        return;
    }
    g_Task->step++;
    func_801F3244();
}
