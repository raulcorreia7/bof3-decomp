#include "battle_15.h"

/* @increments byte at offset 1 of the scratchpad pointer if g_Battle.state has bit
 * 2 set. Uses volatile casts for scratchpad access (0x1F80xxxx).
 */
MATCH void func_800AE438(void) {
    volatile u8* sp_byte;

    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        sp_byte    = *(u8**)(SP(0x44u));
        sp_byte[1] = sp_byte[1] + 1;
    }
}
