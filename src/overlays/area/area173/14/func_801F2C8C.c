#include "area173_14.h"

MATCH void func_801F2C8C(void) {
    g_Task->unk_09 = 0;
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x80)) {
        g_Task->header.step = 5;
    } else {
        g_Task->header.step++;
    }
}
