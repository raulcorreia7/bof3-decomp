#include "area077_14.h"

MATCH void func_801F307C(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x25)) {
        if (SYS_TestFlag(g_SceneFlags, 0x26)) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x06));
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x04));
        }
    }
    SYS_ClearFlag(g_SceneFlags, 0x2D);
    Actor_Clear();
}
