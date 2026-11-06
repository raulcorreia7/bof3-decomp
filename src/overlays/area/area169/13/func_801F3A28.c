#include "area169_13.h"

MATCH s32 func_801F3A28(void) {
    if (D_80143F03 == 1) {
        if (!SYS_TestFlag(g_SaveData.scene_event_flags, 0x74)) {
            Game_SetScriptActive();
            g_SaveData.scene_event.mode = 0x2F;
            g_SaveData.scene_event.step = 0;
            return 1;
        }
    }
    return 0;
}
