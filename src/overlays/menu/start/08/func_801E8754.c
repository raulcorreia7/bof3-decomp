#include "start_08.h"

MATCH s32 func_801E8754(s32 character_index, s32 record_index) {
    Character* rec;
    u8         a;
    u8         b;

    if ((record_index & BYTE_MASK) == 0) {
        rec = &g_SaveData.characters[character_index & BYTE_MASK];
    } else {
        rec = (Character*)&D_80145F04[(character_index & BYTE_MASK) * BATTLE_PARTY_STRIDE];
    }
    a = Char_AddWillpower((&rec->base.willpower), 1);
    b = Char_AddWillpower((&rec->stats.willpower), 1);
    if ((a != 0) || (b != 0)) {
        return 0;
    }
    return 4;
}
