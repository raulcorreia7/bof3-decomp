#include "engine/slus/slus.h"

/* sets the active selection cue: resolves the selection's two cue
 * bytes, starts and stops the cue, stores the level, and publishes the id.
 */
MATCH void SND_PlayBgm(s32 selection_id, s32 cue_level, s32 cue_shape) {
    u32 index;

    if ((selection_id & BYTE_MASK) != GAME_NONE) {
        index = (selection_id & BYTE_MASK) * 4;
        SND_PlaySequence(((u8*)g_SelectionCues)[index], ((u8*)D_80181EBB)[index], 0, 0);
        SND_FadeInSequence(((u8*)g_SelectionCues)[index], ((u8*)D_80181EBB)[index], (u8)cue_level, (u8)cue_shape);
        D_80143F20 = cue_level & BYTE_MASK;
        g_SndBgmId = (u8)selection_id;
    }
}
