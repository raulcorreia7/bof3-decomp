#include "engine/slus/slus.h"

/* starts the sound entry when the requested selection disagrees with the
 * active one, or when no selection is active.
 */
MATCH s32 SND_RequestBgm(s32 requested) {
    u8  current;
    u16 value;

    /* Byte-offset form: a plain array index spills the address pseudo and
     * leaves an unused 8-byte frame slot that retail does not have. */
    current = g_SndBgmId;
    value   = *(u16*)((u8*)D_80181EB8 + ((requested & BYTE_MASK) << 2));
    if ((value != *(u16*)((u8*)D_80181EB8 + (current << 2))) || (current == GAME_NONE)) {
        EMI_LoaderStreamInitSlot(value);
        return 1;
    }
    return 0;
}
