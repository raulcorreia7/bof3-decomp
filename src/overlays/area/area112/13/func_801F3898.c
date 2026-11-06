#include "area112_13.h"

MATCH void func_801F3898(void) {
    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 0) {
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3CU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3DU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3EU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3FU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x38U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x39U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3AU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x3BU);
        SND_PlayCue(0x200U);
    }
}
