#include "engine/slus/slus.h"

/* records the current EMI dispatch handler for the active ring slot,
 * marks that slot active, and advances the loader step.
 */
MATCH void EMI_LoaderQueuePayload(void) {
    s8*           flag;
    volatile u32* handlers;

    flag            = (s8*)&g_EmiRingSlot;
    handlers        = (u32*)((flag + 0x2F));
    handlers[*flag] = g_EmiLoadArg;
    /* FAKE: barrier reproduces slot index reload ordering. */
    MATCH_BARRIER();
    g_EmiRingStates[*flag] = 1;

    if (g_EmiStep == 0) {
        g_EmiRingStates[*flag] = 2;
    }

    g_EmiStep += 1;
}
