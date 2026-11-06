#include "area056_13.h"

MATCH s32 func_801F346C(void) {
    s32 bit;

    SYS_SetFlag(g_SaveData.scene_event_flags, 0x6E);
    for (bit = 0x6D; bit < 0x71; bit++) {
        if (SYS_TestFlag(g_SaveData.scene_event_flags, bit) == 0) {
            return 0;
        }
    }
    SYS_SetFlag(g_SaveData.scene_event_flags, 0x71);
    return 0;
}
