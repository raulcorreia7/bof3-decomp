#include "engine/slus/slus.h"

/* selects the current EMI entry's primary destination, advances the loader state machine. */
MATCH void EMI_LoadSoundCues(void) {
    if (EMI_LOADER_STEP == 0) {
        g_EmiLoadArg = g_EmiBanks[D_80146483].cue_table;
    }

    EMI_CopySectorData();
    EMI_LOADER_STEP += 1;
}
