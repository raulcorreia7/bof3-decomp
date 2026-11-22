#include "engine/slus/slus.h"

/* waits for the overlay loader, then starts the selection cue of the
 * requested selection unless it is already the active one.
 */
MATCH void SND_BGMStart(u8 bgm_id, u8 cue_level, u8 cue_shape) {
    if (bgm_id != GAME_NONE) {
        if ((SND_BGMRequest(bgm_id) & BYTE_MASK) != 0) {
            while (!EMI_IsReady()) {
                SYS_ThreadWait(1);
            }
        }
        if (g_SndBGMId != bgm_id) {
            SND_BGMPlay(bgm_id, cue_level, cue_shape);
        }
    }
}
