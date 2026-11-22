#include "area030_04.h"

/* When the AREA030 state byte is 3, advances the sub-state and bumps
 * the scratchpad step byte, then runs the shared world update. */
MATCH void func_801DC514(void) {
    if (D_80144199 == 3) {
        func_801DDE94(3);
        TASK(FishingState)->sub_index += 1;
    }
    Script_AnimStepLoop();
}
