#include "start_08.h"

/* Glyph tables and the per-record meter step used by the prompt loop. */

MATCH s32 func_801E7F8C(s32 slot_count, s32 record_index) {
    u8  i;
    s32 result;

    result = 0;
    for (i = 0; i < (Party_CountOrder(0) & 0xFF); i++) {
        result |= Char_RestoreHP(g_CharSlot[D_80144F5A[i]], 0x64, record_index & 0xFF);
    }
    return -((result & 0xFF) == 0) & 3;
}
