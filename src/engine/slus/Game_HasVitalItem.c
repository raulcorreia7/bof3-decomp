#include "engine/slus/slus.h"

/* forwards the byte at **cursor to Party_HasVitalItem and returns its low
 * 8 bits.
 */
MATCH s32 Game_HasVitalItem(u8** cursor) {
    return Party_HasVitalItem((s32) * *cursor) & BYTE_MASK;
}
