#include "start_08.h"

/* func_801E81D4 */
MATCH s32 Item_CureBlind(u8 character_index, u8 record_index) {
    return (Char_ClearStatus(character_index, STATUS_BLIND, record_index) & BYTE_MASK) == 0 ? 3 : 0;
}
