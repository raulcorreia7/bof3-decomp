#include "start_08.h"

MATCH s32 func_801E8754(s32 character_index, s32 record_index) {
    Character* rec;
    u8         a;
    u8         b;

    if ((record_index & BYTE_MASK) == 0) {
        rec = &g_Characters[character_index & BYTE_MASK];
    } else {
        rec = &g_BattlePartyBattlers[character_index & BYTE_MASK].chr;
    }
    a = Char_AddWillpower((&rec->base.willpower), 1);
    b = Char_AddWillpower((&rec->stats.willpower), 1);
    if ((a != 0) || (b != 0)) {
        return 0;
    }
    return 4;
}
