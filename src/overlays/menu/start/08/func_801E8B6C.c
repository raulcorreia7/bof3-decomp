#include "start_08.h"

MATCH s32 func_801E8B6C(u8 character_index, u8 record_index) {
    return (Char_RestoreHP(character_index, 0x5, record_index) & 0xFF) == 0 ? 3 : 0;
}
