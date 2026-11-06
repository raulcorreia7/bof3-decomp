#include "area193_13.h"

MATCH void func_801F31C0(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x8A)) {
        g_SaveData.scene_event.mode = 0x39;
        g_AreaDrawFlags             = 0;
        g_SaveData.scene_event.step = 0x14;
    } else {
        g_GameRequestKind = 1;
    }
}
