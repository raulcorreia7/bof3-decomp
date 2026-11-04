#include "engine/slus/slus.h"

/* starts the selection's cue effect: for any selection byte other
 * than 0xFF, passes the two bytes of the selection's table row and the cue
 * level and shape, both narrowed to a byte, to func_8015D554.
 */
MATCH void SND_FadeOutBgm(u8 selection_id, s32 cue_level, s32 cue_shape) {
    if (selection_id != GAME_NONE) {
        SND_FadeOutSequence(g_SelectionCues[selection_id * 4], D_80181EBB[selection_id * 4], cue_level & BYTE_MASK,
                            cue_shape & BYTE_MASK);
    }
}
