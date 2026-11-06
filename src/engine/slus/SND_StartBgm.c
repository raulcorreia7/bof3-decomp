#include "engine/slus/slus.h"

/* waits for the overlay loader, then starts the selection cue of the
 * requested selection unless it is already the active one.
 */
MATCH void SND_StartBgm(u8 bgm_id, u8 cue_level, u8 cue_shape) {
    if (bgm_id != GAME_NONE) {
        if ((SND_RequestBgm(bgm_id) & BYTE_MASK) != 0) {
            while (!EMI_LoaderIsReady()) {
                CallbackWait(1);
            }
        }
        if (g_SndBgmId != bgm_id) {
            SND_PlayBgm(bgm_id, cue_level, cue_shape);
        }
    }
}
