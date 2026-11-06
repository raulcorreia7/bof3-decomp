#include "area108_14.h"

MATCH s32 func_801F4A18(void) {
    if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x1E)) {
        g_CurrentActor->unk_77 = 0x12;
    } else if (SYS_TestFlag(g_SaveData.scene_event_flags, 0x1F)) {
        g_CurrentActor->unk_77 = 0x11;
    }
    g_CurrentActor->unk_7E = 0xFFFE;
}
