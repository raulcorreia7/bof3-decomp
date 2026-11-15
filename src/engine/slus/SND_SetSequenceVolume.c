#include "engine/slus/slus.h"

/* refreshes the SsSepVol pair from the paused stream state and forwards
 * the caller's byte-selected volume entry to SsSepSetVol.
 */
MATCH void SND_SetSequenceVolume(s32 group, s16 sequence, s16 left_volume, s16 right_volume) {
    u16 vA;
    u16 vB;

    vA         = D_80148A04;
    vB         = D_80148A06;
    D_8018B418 = vA;
    D_8018B41A = vB;
    SsSepSetVol(g_SelectionEffectVoices[group & HALF_MASK], sequence, left_volume, right_volume);
}
