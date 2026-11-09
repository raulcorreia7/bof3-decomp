/* Reads the byte at offset 0x03 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */

#include "area030_04.h"

/* func_801DA5B4 */
MATCH void Fishing_CastRun(void) {
    Callback handler = g_FishingCastStates[g_Task->unk_03];
    handler();
}
