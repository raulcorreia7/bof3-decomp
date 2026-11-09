#include "engine/slus/slus.h"

/* ducks the selection effect. */
MATCH void SND_FadeOutSequence(u32 effect_group, s32 effect_id, s32 cue_level, s32 cue_shape) {
    if (D_80144954 == 0) {
        D_8018B418 = 0x1F;
        D_8018B41A = 0x1F;
        SsSepSetDecrescendo(g_SelectionFxVoices[effect_group & HALF_MASK], effect_id, cue_level, cue_shape);
        SsSepStop(g_SelectionFxVoices[effect_group & HALF_MASK], effect_id);
    }
}
