#include "area105_13.h"

MATCH void func_801F2CDC(void) {
    if (g_AreaSceneMode == 2) {
        SND_PlayCue(EMI_CUE_ID(2, 6));
        SND_PlayCue(EMI_CUE_ID(2, 3));
        FIELD(u8, g_Task, 0x2u)++;
    }
    func_801F2D9C(0);
}
