#include "engine/slus/slus.h"

/* ducks the selection effect: with D_80144954 clear it pins both stream volume cells to 0x1F, passes the
 * voice entry of the effect group (g_SelectionFxVoices) to SsSepSetDecrescendo with the effect id and cue level, then
 * stops the voice through SsSepStop.
 */
MATCH void SND_FadeOutSequence(u32 effect_group, s32 effect_id, s32 cue_level, s32 cue_shape) {
    if (D_80144954 == 0) {
        D_8018B418 = 0x1F;
        D_8018B41A = 0x1F;
        SsSepSetDecrescendo(g_SelectionFxVoices[effect_group & HALF_MASK], (s16)effect_id, (s16)cue_level, cue_shape);
        SsSepStop(g_SelectionFxVoices[effect_group & HALF_MASK], (s16)effect_id);
    }
}
