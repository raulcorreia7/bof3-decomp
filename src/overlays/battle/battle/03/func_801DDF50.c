#include "battle_03.h"

MATCH u8 func_801DDF50(u16 entry_id, u32 table_kind) {
    u32* table;
    u32* entry;
    u32  id;

    table = *(u32**)((char*)D_800B6178 + ((table_kind & BYTE_MASK) << 2));
    if (table == (u32*)0) {
        /* no table for this kind */
        goto no_match;
    }
    entry = table;
    if (*entry == 0xFFFFFFFFu) {
        /* empty table */
        goto no_match;
    }
    id = entry_id & BYTE_MASK;
    while ((*entry != 0xFFFFFFFFu) && (*(u16*)((u8*)entry + 2) != id)) {
        entry += 1;
    }
    if (*entry != 0xFFFFFFFFu) {
        /* matched entry: submit its effect id */
        goto call_effect;
    }

no_match:
    return 1u;

call_effect:
    SND_StartXAStream((*entry & HALF_MASK) + 0x1000u, 1u);
    return 0u;
}
