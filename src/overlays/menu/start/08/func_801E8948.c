#include "start_08.h"

MATCH s32 func_801E8948(s32 slot_count, u8 record_index) {
    u8  i;
    s32 changed;

    changed = 0;
    for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
        changed |= Char_RestoreHP(g_CharSlot[g_PartyFieldOrder[i]], 80, record_index);
    }
    return (changed & BYTE_MASK) == 0 ? 3 : 0;
}
