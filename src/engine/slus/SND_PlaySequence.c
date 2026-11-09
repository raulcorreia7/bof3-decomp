#include "engine/slus/slus.h"

/* stops the effect voice that the group's entry in g_SelectionFxVoices names. */
MATCH void SND_PlaySequence(u16 group, s32 sequence, s32 left_volume, s32 right_volume) {
    s16 seq;

    seq = sequence;
    SsSepStop(g_SelectionFxVoices[group & HALF_MASK], seq);
    if (D_80144954 == 0u) {
        D_8018B418 = 0x1FFF;
        D_8018B41A = 0x1FFF;
        SsSepSetVol(g_SelectionFxVoices[group & HALF_MASK], seq, left_volume, right_volume);
    } else {
        SsSepSetVol(g_SelectionFxVoices[group & HALF_MASK], seq, 0, 0);
    }
    SsSepPlay(g_SelectionFxVoices[group & HALF_MASK], seq, SSPLAY_PLAY, 1);
}
