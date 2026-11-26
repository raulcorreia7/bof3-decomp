#include "area030_04.h"

/* When the AREA030 state byte is 3, arms the alternate selection cue
 * and advances the sub-state to 2, then runs the shared world update. */
MATCH void func_801DAFBC(void) {
    if (g_SpawnedActors[4].header.mode == 3) {
        SND_SeqStop(0, 0);
        SND_BGMPlay(0x29, 0x64, 8);
        func_801DDE94(2);
        g_SpawnedActors[5].header.mode += 1;
        SELF(FishingState)->timer = 0;
        SELF(FishingState)->sub_index += 1;
    }
    Script_AnimStepLoop();
}
