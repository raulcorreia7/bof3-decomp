#include "area111_13.h"

MATCH void func_801F3130(void) {
    g_Task->unk_30 = 0;
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x28) != 0) {
        Actor_Clear();
        return;
    }
    g_Task->header.step++;
    func_801F3244();
}
