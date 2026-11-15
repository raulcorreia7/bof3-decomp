#include "engine/slus/slus.h"

/* copies the current type-0 EMI payload to RAM, then advances the
 * loader's completed-entry count.
 */
MATCH void EMI_LoadToRam(void) {
    s32* completed_entries;

    EMI_CopySector();
    completed_entries  = &g_EmiStep;
    *completed_entries = *completed_entries + 1;
}
