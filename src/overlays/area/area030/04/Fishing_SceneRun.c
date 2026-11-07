/* Reads the byte at offset 0x02 of the scratchpad work object
 * pointed at by the non-volatile pointer cell at 0x1F800044, then calls the
 * handler stored at that index in the g_FishingSceneModes dispatch table. */

#include "area030_04.h"

/* func_801D9B14 */
MATCH void Fishing_SceneRun(void) {
    u8*      work    = TASK_BYTES;
    Callback handler = g_FishingSceneModes[work[2]];
    handler();
}
