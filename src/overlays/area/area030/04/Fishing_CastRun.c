/* Reads the byte at offset 0x03 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the g_FishingCastStates dispatch table. */

#include "area030_04.h"

/* func_801DA5B4 */
MATCH void Fishing_CastRun(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = g_FishingCastStates[work[3]];
    handler();
}
