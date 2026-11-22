#include "engine/slus/slus.h"

/* selects the current EMI entry's primary destination, advances the
 * loader state machine, and advances the loader step.
 */
MATCH void EMI_LoadSE(void) {
    if (EMI_LOADER_STEP == 0) {
        g_EmiStream.load_arg = g_EmiBanks[g_EmiStream.entry_bank].se_records;
    }

    EMI_SectorCopy();
    EMI_LOADER_STEP += 1;
}
