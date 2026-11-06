#include "start_08.h"

/* Glyph tables and the per-record meter step used by the prompt loop. */

MATCH s32 func_801E7F8C(s32 slot_count, s32 record_index) {
    u8  i;
    s32 result;

    result = 0;
    for (i = 0; i < (Party_CountOrder(0) & BYTE_MASK); i++) {
        result |= Char_RestoreHP(g_CharSlot[D_80144F5A[i]], 0x64, record_index & BYTE_MASK);
    }
    return -((result & BYTE_MASK) == 0) & 3;
}
