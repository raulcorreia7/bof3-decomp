#include "start_08.h"

MATCH s32 func_801E88E0(u8 character_index, u8 record_index) {
    return (Char_RestoreAP(character_index, 0x5, record_index) & 0xFF) == 0 ? 3 : 0;
}
