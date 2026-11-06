#include "start_08.h"

MATCH s32 func_801E82F8(s32 first_index, u8 last_index, s32 update_mask) {
    u8 flags;
    u8 id;
    u8 i;

    flags = 0;
    for (i = 0; i < Party_CountOrder(0); i++) {
        id = g_CharSlot[D_80144F5A[i]];
        flags |= Char_ClearStatus(id, 0xA0, last_index);
        flags |= Char_RestoreHP(id, 0, last_index);
    }
    return (flags & BYTE_MASK) == 0 ? 3 : 0;
}
