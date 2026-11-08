#include "area105_13.h"

MATCH void func_801F2C48(void) {
    if (SCENE_PROGRESS == 0x20C) {
        SND_PlayCue(EMI_CUE_ID(2, 2));
        FIELD(u8, g_Task, 0x2u)++;
    }
}
