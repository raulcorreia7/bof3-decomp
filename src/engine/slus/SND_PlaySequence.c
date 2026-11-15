#include "engine/slus/slus.h"

/* stops the effect voice that the sep_slot's entry in g_SelectionEffectVoices names, then either pins both stream volume
 * cells to 0x1FFF and forwards the sequencer id and volume pair to SsSepSetVol, or silences the voice while the duck
 * gate D_80144954 is set, and finally starts it through SsSepPlay (mode 1, level 1).
 */
MATCH void SND_PlaySequence(u16 sep_slot, s32 sequence, s32 left_volume, s32 right_volume) {
    s16 seq;

    seq = sequence;
    SsSepStop(g_SelectionEffectVoices[sep_slot & HALF_MASK], seq);
    if (D_80144954 == 0u) {
        D_8018B418 = 0x1FFF;
        D_8018B41A = 0x1FFF;
        SsSepSetVol(g_SelectionEffectVoices[sep_slot & HALF_MASK], seq, left_volume, right_volume);
    } else {
        SsSepSetVol(g_SelectionEffectVoices[sep_slot & HALF_MASK], seq, 0, 0);
    }
    SsSepPlay(g_SelectionEffectVoices[sep_slot & HALF_MASK], seq, SSPLAY_PLAY, 1);
}
