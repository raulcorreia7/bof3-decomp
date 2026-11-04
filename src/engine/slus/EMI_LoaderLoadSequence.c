#include "engine/slus/slus.h"

/* selects the current EMI entry's alternate destination, marks the
 * entry with flag 2, advances the loader state machine, and advances the step.
 */
MATCH void EMI_LoaderLoadSequence(void) {
    u32 entry_offset;

    if (EMI_LOADER_STEP == 0) {
        entry_offset = D_80146483 * sizeof(EmiBank);
        g_EmiLoadArg = *(u32*)((u8*)&D_8014677C[0].sequence_buffer + entry_offset);
        *(u16*)((u8*)&D_8014677C[0].flags + entry_offset) |= 2;
    }

    EMI_LoaderCopySector();
    EMI_LOADER_STEP += 1;
}
