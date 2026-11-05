#include "area105_13.h"

MATCH void func_801F2C48(void) {
    /* FAKE: retail reads g_SceneState.state_04 as u16. */
    if ((*(u16*)&g_SceneState.state_04) == 0x20C) {
        SND_PlayCue(EMI_CUE_ID(2, 2));
        FIELD(u8, g_Task, 0x2u)++;
    }
}
