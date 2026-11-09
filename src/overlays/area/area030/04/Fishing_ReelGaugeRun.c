#include "area030_04.h"

/* Reads byte 0x01 of the scratchpad work object pointed at by the non-volatile pointer cell at 0x1F800044. */
/* func_801D2BF0 */
MATCH void Fishing_ReelGaugeRun(void) {
    Callback handler;

    handler = g_FishingReelGaugeStates[g_Task->header.mode];
    handler();
}
