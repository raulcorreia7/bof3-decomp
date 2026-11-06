#include "area171_13.h"

MATCH s32 func_801F3EBC(void) {
    if (D_80143F03 == 3) {
        if (!SYS_TestFlag(g_SaveData.scene_event_flags, 0x74)) {
            Game_SetScriptActive();
            g_SaveData.scene_event.mode = 0x30;
            g_SaveData.scene_event.step = 0;
            return 1;
        }
    }
    return 0;
}
