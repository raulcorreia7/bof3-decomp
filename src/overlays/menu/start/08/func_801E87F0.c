#include "start_08.h"

/* First shop record table; the fade helper lives in the EXE overlay. */

MATCH s32 func_801E87F0(s32 record_index, s32 use_battle_record) {
    Character* rec;
    u16        cur;
    u16        limit;

    if ((use_battle_record & BYTE_MASK) == 0) {
        rec = &g_Characters[record_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(record_index & BYTE_MASK) * BATTLE_PARTY_STRIDE];
    }
    limit = rec->stats.max_hp;
    cur   = rec->current_hp;
    if (cur == limit) {
        return 3;
    }
    if (rec->fatigue < 9) {
        rec->fatigue = (u8)(rec->fatigue + 1);
        Char_RebuildStats(rec);
        rec->current_hp = rec->stats.max_hp;
    } else if (cur < limit) {
        rec->current_hp = limit;
    } else {
        return 3;
    }
    return 0;
}
