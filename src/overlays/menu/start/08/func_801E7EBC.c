#include "start_08.h"

MATCH s32 func_801E7EBC(u8 character_index, u8 record_index) {
    return (Char_RestoreHP(character_index, 20, record_index) & BYTE_MASK) == 0 ? 3 : 0;
}
