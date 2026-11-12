#include "start_08.h"

MATCH s32 func_801E88AC(u8 character_index, u8 record_index) {
    return (Char_RestoreHP(character_index, 1, record_index) & BYTE_MASK) == 0 ? 3 : 0;
}
