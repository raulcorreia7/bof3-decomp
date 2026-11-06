#include "area111_13.h"

MATCH void func_801F319C(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x28)) {
        FIELD(u8, g_Task, 0x2u)++;
    }
    func_801F3244();
}
