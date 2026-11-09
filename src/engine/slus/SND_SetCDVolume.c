#include "engine/slus/slus.h"

/* Latch the CD level and write the CD attenuator: stereo (g_SndMono == 0) routes the level to val0 and val2,
 * mono sends half the level to all four.
 */
MATCH void SND_SetCDVolume(u8 volume) {
    /* FAKE: volatile pointee keeps one materialized level address. */
    volatile u8* level = &g_SndCDVolume;
    u8           current;
    u8           half;

    *level = volume;
    if (g_SndMono == 0) {
        g_SndCDMix.val1 = 0;
        g_SndCDMix.val3 = 0;
        current         = *level;
        g_SndCDMix.val0 = current;
        g_SndCDMix.val2 = current;
    } else {
        half            = *level >> 1;
        g_SndCDMix.val0 = half;
        g_SndCDMix.val1 = half;
        g_SndCDMix.val2 = half;
        g_SndCDMix.val3 = half;
    }
    CdMix(&g_SndCDMix);
}
