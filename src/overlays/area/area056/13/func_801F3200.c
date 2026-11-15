#include "area056_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3200(void) {
    MESSAGE_REQUEST_CLEAR();
    /* FAKE: pure C leaves the prologue first and the choice load ahead of the clear. */
    FAKE_BARRIER();
    if (g_MessageChoice != 0) {
        return;
    }

    SND_PlayCue(0x208);
    if ((D_80144EA1 & 0x7F) != 0x7F) {
        return;
    }

    *D_80145E91 = 2;
    *D_80145E92 = 7;
    *D_80145E93 = 0;
    Area_SetCellPalette(D_80145EC6, D_80145ECA);
}
#else
INCLUDE_ASM(func_801F3200);
#endif
