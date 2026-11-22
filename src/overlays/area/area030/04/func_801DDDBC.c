#include "area030_04.h"

/* Starts the AREA030 leave transition: selects the destination
 * palette, sets the state bytes, advances the sub-state and the scratchpad step
 * byte, then runs the shared world update. */
MATCH void func_801DDDBC(void) {
    Script_Request(9);
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
    D_80144125 = 7;
    D_8014419E = 3;
    D_80144199 += 1;
    TASK(FishingState)->sub_index += 1;
    Script_AnimStepLoop();
}
