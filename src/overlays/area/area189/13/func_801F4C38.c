#include "area189_13.h"

MATCH void func_801F4C38(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x82)) {
        g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    }
}
