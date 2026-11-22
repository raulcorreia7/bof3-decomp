#include "engine/slus/slus.h"

/* copies the current type-0 EMI payload to RAM, then advances the
 * loader's completed-entry count.
 */
MATCH void EMI_LoadToRam(void) {
    s32* completed_entries;

    EMI_SectorCopy();
    completed_entries  = &g_EmiStream.step;
    *completed_entries = *completed_entries + 1;
}
