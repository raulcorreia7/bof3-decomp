#include "area077_14.h"

MATCH void func_801F56C4(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 7) != 0) {
        TASK_BYTES[2]++;
    }
}
