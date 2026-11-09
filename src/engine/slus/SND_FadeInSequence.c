#include "engine/slus/slus.h"

/* starts the effect group's crescendo. */
MATCH void SND_FadeInSequence(s32 group, s16 sequence, s16 volume, s32 time) {
    if (D_80144954 != 0) {
        return;
    }
    D_8018B418 = 0x7FF;
    D_8018B41A = 0x7FF;
    SsSepSetCrescendo(g_SelectionFxVoices[group & HALF_MASK], sequence, volume, time);
}
