#include "engine/slus/slus.h"

/* selects the current EMI entry's primary destination, advances the
 * loader state machine, and advances the loader step.
 */
MATCH void EMI_LoaderLoadVabCues(void) {
    if (EMI_LOADER_STEP == 0) {
        g_EmiLoadArg = D_8014677C[D_80146483].cue_table;
    }

    EMI_LoaderCopySector();
    EMI_LOADER_STEP += 1;
}
