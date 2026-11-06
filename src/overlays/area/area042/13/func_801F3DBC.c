#include "area042_13.h"

MATCH void func_801F3DBC(void) {
    g_CurrentActor->interaction_flags &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if ((g_CharSlot[D_80145F09] == 1) && (SYS_TestFlag(g_SaveData.scene_event_flags, 0xB) == 0) &&
        (SYS_TestFlag(g_SaveData.scene_event_flags, 0x11) == 0)) {
        SYS_SetFlag(g_SaveData.scene_event_flags, 0xBU);
        g_SaveData.scene_event.mode = 7;
        g_SaveData.scene_event.step = 0xA;
        D_801448EE                  = 0x384;
        g_GameFlags |= 0x20;
    }
}
