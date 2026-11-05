#include "area042_13.h"

MATCH void func_801F3DBC(void) {
    g_CurrentActor->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING;
    if ((g_CharSlot[D_80145F09] == 1) && (SYS_TestFlag(g_SceneEventFlags, 0xB) == 0) &&
        (SYS_TestFlag(g_SceneEventFlags, 0x11) == 0)) {
        SYS_SetFlag(g_SceneEventFlags, 0xBU);
        D_801448EB = 7;
        D_801448EC = 0xA;
        D_801448EE = 0x384;
        g_GameFlags |= 0x20;
    }
}
