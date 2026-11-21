#include "engine/slus/slus.h"

/* starts the sound entry when the bgm_id selection disagrees with the
 * active one, or when no selection is active.
 */
MATCH bool SND_RequestBGM(s32 bgm_id) {
    u8  current;
    u16 value;

    /* Byte-offset form: a plain array index spills the address pseudo and
     * leaves an unused 8-byte frame slot that retail does not have. */
    current = g_SndBGMId;
    value   = *(u16*)((u8*)g_BGMTracks + ((bgm_id & BYTE_MASK) << 2));
    if ((value != *(u16*)((u8*)g_BGMTracks + (current << 2))) || (current == GAME_NONE)) {
        EMI_LoadArchive(value);
        return 1;
    }
    return 0;
}
