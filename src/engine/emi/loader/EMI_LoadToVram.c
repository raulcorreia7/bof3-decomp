#include "engine/slus/slus.h"

/* on the first call resets the strip and unpacks its kind, row and entry count from g_EmiLoadArg; every call
 * marks the g_EmiRingSlot entry ready in g_EmiRingStates, writes the slot's dispatch word into the ring entry
 * table at g_EmiStep + 76, advances g_EmiVramStep (wrapping to 0 and advancing g_EmiVramRow at
 * g_EmiVramEntryCount) and counts the step at g_EmiStep. */
MATCH void EMI_LoadToVram(void) {
    u32* loader_step;
    u32* dispatches;
    u32  packed;
    u32  dispatch;
    u8   next_index;

    loader_step = &g_EmiStep;
    if (*loader_step == 0) {
        g_EmiVramStep       = 0;
        packed              = g_EmiLoadArg;
        g_EmiVramType       = (packed >> 24) & 0x3F;
        g_EmiVramRow        = (packed >> 16) & 0x1F;
        g_EmiVramEntryCount = (packed >> 8) & 0x3F;
    }

    g_EmiRingStates[g_EmiRingSlot] = 3;
    dispatch                       = g_EmiVramStep;
    next_index                     = g_EmiVramStep + 1;
    g_EmiVramStep                  = next_index;
    dispatches                     = loader_step + 19;
    dispatches[g_EmiRingSlot]      = ((dispatch + g_EmiVramType) << 24) + (g_EmiVramRow << 16);

    if (next_index >= g_EmiVramEntryCount) {
        g_EmiVramStep = 0;
        g_EmiVramRow++;
    }

    *loader_step = *loader_step + 1;
}
