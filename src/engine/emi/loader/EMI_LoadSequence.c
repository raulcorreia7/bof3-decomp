#include "engine/slus/slus.h"

/* selects the current EMI entry's alternate destination, marks the
 * entry with flag 2, advances the loader state machine, and advances the step.
 */
MATCH void EMI_LoadSequence(void) {
    if (EMI_LOADER_STEP == 0) {
        g_EmiStream.load_arg = g_EmiBanks[g_EmiStream.entry_bank].sequence_buffer;
        g_EmiBanks[g_EmiStream.entry_bank].flags |= 2;
    }

    EMI_SectorCopy();
    EMI_LOADER_STEP += 1;
}
