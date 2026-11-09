#include "engine/slus/slus.h"

/* starts the selection's cue effect. */
MATCH void SND_FadeOutBGM(u8 selection_id, s32 cue_level, s32 cue_shape) {
    if (selection_id != GAME_NONE) {
        SND_FadeOutSequence(g_SelectionCues[selection_id * 4], g_SelectionSequences[selection_id * 4],
                            cue_level & BYTE_MASK, cue_shape & BYTE_MASK);
    }
}
