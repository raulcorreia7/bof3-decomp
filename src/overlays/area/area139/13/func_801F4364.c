#include "area139_13.h"

/* Sets the flag bit of the trigger record that matches the two arguments and queues its cue. */
MATCH s32 func_801F4364(s32 arg0, s32 arg1) {
    s32 i;
    s32 off;
    u8* mode;

    i = 0;
    arg0 &= BYTE_MASK;
    arg1 &= BYTE_MASK;
    mode = &D_80145E98;
    off  = 0;
    for (; i < 2; i++, off += 4) {
        if (arg0 == D_801F45E4[off] && arg1 == D_801F45E4[off + 1] && (D_801F45E4[off + 2] & 0xF) == *mode) {
            break;
        }
    }
    if (i == 2) {
        return 0;
    }
    SYS_ToggleFlag(g_SceneEventFlags, D_801F45E4[i * 4 + 3]);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
    return 1;
}
