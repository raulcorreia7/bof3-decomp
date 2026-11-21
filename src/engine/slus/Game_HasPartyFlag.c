#include "engine/slus/slus.h"

/* reports bit 0 of the +0x6F flag of the 0xA4-stride record selected by
 * the byte at *cursor.
 */
/* func_8015B7F0 */
/* Script condition: the named character has the party flag set. */
MATCH s32 Game_HasPartyFlag(u8** cursor) {
    s16 flags;

    flags = g_Characters[**cursor].party_flags;
    if (0x1 & flags) {
        return 1;
    }
    flags = 0;
    return flags;
}
