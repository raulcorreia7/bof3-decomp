#include "area112_13.h"

MATCH void func_801F3898(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 0) {
        SYS_ClearFlag(g_SceneEventFlags, 60U);
        SYS_ClearFlag(g_SceneEventFlags, 61U);
        SYS_ClearFlag(g_SceneEventFlags, 62U);
        SYS_ClearFlag(g_SceneEventFlags, 63U);
        SYS_ClearFlag(g_SceneEventFlags, 56U);
        SYS_ClearFlag(g_SceneEventFlags, 57U);
        SYS_ClearFlag(g_SceneEventFlags, 58U);
        SYS_ClearFlag(g_SceneEventFlags, 59U);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00));
    }
}
