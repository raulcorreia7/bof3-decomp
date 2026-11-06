#include "start_08.h"

MATCH s32 func_801E8914(u8 character_index, u8 record_index) {
    return (Char_RestoreHP(character_index, 0x50, record_index) & 0xFF) == 0 ? 3 : 0;
}
