#include "area030_04.h"

/* When the AREA030 state byte is 3, arms the alternate selection cue
 * and advances the sub-state to 2, then runs the shared world update. */
MATCH void func_801DAFBC(void) {
    if (D_80144199 == 3) {
        SND_SeqStop(0, 0);
        SND_BGMPlay(0x29, 0x64, 8);
        func_801DDE94(2);
        D_8014420D += 1;
        TASK(FishingState)->timer = 0;
        TASK(FishingState)->sub_index += 1;
    }
    Script_AnimStepLoop();
}
