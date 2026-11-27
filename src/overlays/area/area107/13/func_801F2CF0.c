#include "area107_13.h"

MATCH void func_801F2CF0(void) {
    if (g_PadStates[0].held != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        SYS_ToggleFlag(g_SceneEventFlags, 79);
        FIELD(u8, g_Self, 0x9u) = 0x3C;
        FIELD(u8, g_Self, 0x1u) = 3;
    }
}
