/* Reads the byte at offset 0x03 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */

#include "area030_04.h"

/* func_801D9B58 */
MATCH void Fishing_EntryRun(void) {
    Callback handler = g_FishingEntryStates[g_Task->unk_03];
    handler();
}
