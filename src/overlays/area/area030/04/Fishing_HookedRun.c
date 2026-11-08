/* Reads the byte at offset 0x03 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the g_FishingHookedStates dispatch table. */

#include "area030_04.h"

/* func_801DAED4 */
MATCH void Fishing_HookedRun(void) {
    Callback handler = g_FishingHookedStates[g_Task->unk_03];
    handler();
}
