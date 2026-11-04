#include "area112_13.h"

MATCH void func_801F3898(void) {
    g_MessageRequest = 0xFFFF;
    if (D_801490C7 == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 0x3CU);
        SYS_ClearFlag(g_SceneEventFlags, 0x3DU);
        SYS_ClearFlag(g_SceneEventFlags, 0x3EU);
        SYS_ClearFlag(g_SceneEventFlags, 0x3FU);
        SYS_ClearFlag(g_SceneEventFlags, 0x38U);
        SYS_ClearFlag(g_SceneEventFlags, 0x39U);
        SYS_ClearFlag(g_SceneEventFlags, 0x3AU);
        SYS_ClearFlag(g_SceneEventFlags, 0x3BU);
        SND_PlayCue(0x200U);
    }
}
