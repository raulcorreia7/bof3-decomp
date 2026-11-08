#include "area030_04.h"

/* Starts the AREA030 leave transition: selects the destination
 * palette, sets the state bytes, advances the sub-state and the scratchpad step
 * byte, then runs the shared world update. */
MATCH void func_801DDDBC(void) {
    Actor_RequestScript(9);
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
    D_80144125 = 7;
    D_8014419E = 3;
    D_80144199 += 1;
    FISHING_STATE->sub_index_03 += 1;
    func_8014D978();
}
