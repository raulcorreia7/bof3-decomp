#include "engine/slus/slus.h"

/* on the first call zeroes the step index and unpacks three fields from the word at 0x80146458; every call
 * marks slot g_EmiRingSlot ready in g_EmiRingStates, writes the slot's dispatch word into g_EmiStep+76, advances the step
 * index (wrapping and bumping D_8018B4A4 at the limit) and increments the step counter at g_EmiStep.
 */
MATCH void EMI_LoaderLoadGraphics(void) {
    u32* loader_step;
    u32* dispatches;
    u32  packed;
    u32  dispatch;
    u8   next_index;

    loader_step = &g_EmiStep;
    if (*loader_step == 0) {
        D_8018B4AC = 0;
        packed     = g_EmiLoadArg;
        D_8018B4A0 = (packed >> 24) & 0x3F;
        D_8018B4A4 = (packed >> 16) & 0x1F;
        D_8018B4A8 = (packed >> 8) & 0x3F;
    }

    g_EmiRingStates[g_EmiRingSlot] = 3;
    dispatch                       = D_8018B4AC;
    next_index                     = D_8018B4AC + 1;
    D_8018B4AC                     = next_index;
    dispatches                     = loader_step + 19;
    dispatches[g_EmiRingSlot]      = ((dispatch + D_8018B4A0) << 24) + (D_8018B4A4 << 16);

    if (next_index >= D_8018B4A8) {
        D_8018B4AC = 0;
        D_8018B4A4++;
    }

    *loader_step = *loader_step + 1;
}
