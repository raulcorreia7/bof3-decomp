#include "start_08.h"

MATCH s32 func_801E84E4(s32 character_index, s32 record_index) {
    Character* rec;
    u8         a;
    u8         b;

    rec = Start_PickPartyRecord(character_index, record_index);
    a   = Char_AddStat(&rec->base.power, 1);
    b   = Char_AddStat(&rec->stats.power, 1);
    if ((a != 0) || (b != 0)) {
        return 0;
    }
    return 4;
}
