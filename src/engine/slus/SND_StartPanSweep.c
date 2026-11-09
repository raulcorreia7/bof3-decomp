#include "engine/slus/slus.h"

/* starts a pan sweep on voice voice from the current level in D_80149010 to the target level in D_80149040. */
MATCH void SND_StartPanSweep(s32 voice) {
    u16 index;

    index = voice;
    SsUtAutoPan(index, D_80149010[index], D_80149040[index], 1);
    D_80149010[index] = D_80149040[index];
}
