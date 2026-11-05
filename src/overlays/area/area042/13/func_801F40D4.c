#include "area042_13.h"

MATCH void func_801F40D4(void) {
    g_CurrentActor->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if ((g_CharSlot[D_80145F09] == 1) && (SYS_TestFlag(g_SceneEventFlags, 0x15) == 0)) {
        SYS_SetFlag(g_SceneEventFlags, 0x15U);
        func_801F4188();
        if (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) {
            g_CurrentActor->unk_7E += 1;
        }
    }
}
