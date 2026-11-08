#include "area030_04.h"

/* Reads byte 0x01 of the scratchpad work object pointed at by the
 * non-volatile pointer cell at 0x1F800044, then calls the handler stored at
 * that index in the g_FishingReelGaugeStates dispatch table. */
/* func_801D2BF0 */
MATCH void Fishing_ReelGaugeRun(void) {
    u8*      work;
    Callback handler;

    work    = (u8*)g_Task;
    handler = g_FishingReelGaugeStates[work[1]];
    handler();
}
