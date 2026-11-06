#include "area049_14.h"

MATCH void func_801F2C80(void) {
    SYS_ClearFlag(g_SaveData.scene_event_flags, 2U);
    SYS_SetFlag(g_SaveData.scene_event_flags, 3U);
}
