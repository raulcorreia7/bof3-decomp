#include "engine/slus/slus.h"

/* sets the active selection cue. */
MATCH void SND_PlayBGM(s32 selection_id, s32 cue_level, s32 cue_shape) {
    u32 index;

    if ((selection_id & BYTE_MASK) != GAME_NONE) {
        index = (selection_id & BYTE_MASK) * 4;
        SND_PlaySequence(((u8*)g_SelectionCues)[index], ((u8*)g_SelectionSequences)[index], 0, 0);
        SND_FadeInSequence(((u8*)g_SelectionCues)[index], ((u8*)g_SelectionSequences)[index], (u8)cue_level,
                           (u8)cue_shape);
        D_80143F20 = cue_level & BYTE_MASK;
        g_SndBGMId = selection_id;
    }
}
