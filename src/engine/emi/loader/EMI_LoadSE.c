#include "engine/slus/slus.h"

/* selects the current EMI entry's primary destination, advances the
 * loader state machine, and advances the loader step.
 */
MATCH void EMI_LoadSE(void) {
    if (EMI_LOADER_STEP == 0) {
        g_EmiLoadArg = g_EmiBanks[g_EmiEntryBank].se_records;
    }

    EMI_SectorCopy();
    EMI_LOADER_STEP += 1;
}
