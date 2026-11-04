#include "engine/slus/slus.h"

/* Latch the CD level and write the CD attenuator: stereo (g_SndMono == 0) routes the level to val0 and val2,
 * mono sends half the level to all four.
 */
MATCH void SND_SetCdVolume(u8 volume) {
    /* FAKE: volatile pointee keeps one materialized level address. */
    volatile u8* level = &g_SndCdVolume;
    u8           current;
    u8           half;

    *level = volume;
    if (g_SndMono == 0) {
        g_SndCdMix.val1 = 0;
        g_SndCdMix.val3 = 0;
        current         = *level;
        g_SndCdMix.val0 = current;
        g_SndCdMix.val2 = current;
    } else {
        half            = *level >> 1;
        g_SndCdMix.val0 = half;
        g_SndCdMix.val1 = half;
        g_SndCdMix.val2 = half;
        g_SndCdMix.val3 = half;
    }
    CdMix(&g_SndCdMix);
}
