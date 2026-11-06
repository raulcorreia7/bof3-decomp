#include "area167_13.h"

MATCH void func_801F49F0(void) {
    if ((D_80143F03 == 0) && (SYS_TestFlag(g_SaveData.scene_event_flags, 0x8F) != 0) &&
        (SYS_TestFlag(g_SaveData.scene_event_flags, 0x90) == 0)) {
        g_AreaCameraOffsetZ         = 0x980;
        g_SaveData.scene_event.mode = 0x20;
        g_SaveData.scene_event.step = 0x1E;
    }
}
