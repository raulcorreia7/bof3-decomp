#include "area107_13.h"

MATCH void func_801F2CF0(void) {
    if (g_InputHeld != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
        SYS_ToggleFlag(g_SceneEventFlags, 79);
        FIELD(u8, g_Task, 0x9u) = 0x3C;
        FIELD(u8, g_Task, 0x1u) = 3;
    }
}
