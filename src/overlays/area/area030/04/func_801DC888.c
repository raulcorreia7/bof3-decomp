#include "area030_04.h"

/* On the AREA030 entry frame (state byte 0) arms the opening cue,
 * advances the world selector and clears the work object's step byte. */
MATCH void func_801DC888(void) {
    if (g_SpawnedActors[3].header.mode == 0) {
        SND_StartDecrescendo(0, 0, 0x14, 0x10);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        g_SpawnedActors[6].header.mode += 1;
        SELF(FishingState)->cue_index = 0;
        SELF(FishingState)->sub_index += 1;
    }
}
