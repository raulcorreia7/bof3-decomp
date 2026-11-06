#include "start_08.h"

MATCH s32 func_801E8A70(s32 slot_count, u8 record_index) {
    u8  i;
    s32 changed;

    changed = 0;
    for (i = 0; i < Party_CountOrder(0); i++) {
        changed |= Char_ClearStatus(g_CharSlot[D_80144F5A[i]], 0x80, record_index);
    }
    return (changed & BYTE_MASK) == 0 ? 3 : 0;
}
