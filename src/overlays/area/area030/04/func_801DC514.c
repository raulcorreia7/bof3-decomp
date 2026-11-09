#include "area030_04.h"

/* When the AREA030 state byte is 3, advances the sub-state and bumps the scratchpad step byte. */
MATCH void func_801DC514(void) {
    if (D_80144199 == 3) {
        func_801DDE94(3);
        FISHING_STATE->sub_index_03 += 1;
    }
    Actor_StepAnimLoop();
}
