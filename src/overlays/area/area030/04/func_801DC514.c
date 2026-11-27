#include "area030_04.h"

/* When the AREA030 state byte is 3, advances the sub-state and bumps
 * the scratchpad step byte, then runs the shared world update. */
MATCH void func_801DC514(void) {
    if (g_SpawnedActors[4].header.mode == 3) {
        func_801DDE94(3);
        SELF(FishingState)->sub_index += 1;
    }
    Script_AnimStepLoop();
}
