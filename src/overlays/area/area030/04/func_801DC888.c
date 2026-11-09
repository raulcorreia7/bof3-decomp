#include "area030_04.h"

/* On the AREA030 entry frame (state byte 0) arms the opening cue,
 * advances the world selector and clears the work object's step byte. */
MATCH void func_801DC888(void) {
    if (D_80144125 == 0) {
        SND_StartDecrescendo(0, 0, 0x14, 0x10);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        D_80144281 += 1;
        FISHING_STATE->cue_index_06 = 0;
        FISHING_STATE->sub_index_03 += 1;
    }
}
