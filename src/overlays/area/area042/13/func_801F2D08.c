#include "area042_13.h"

MATCH void func_801F2D08(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0xB) != 0) {
        g_Task->header.mode = 0;
    }
}
