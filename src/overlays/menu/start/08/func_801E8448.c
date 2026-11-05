#include "start_08.h"

MATCH s32 func_801E8448(s32 character_index, s32 record_index) {
    Character* rec;
    u8         a;
    u8         b;

    rec = Start_PickPartyRecord(character_index, record_index);
    a   = Char_AddCappedStat(&rec->base.max_ap, 1);
    b   = Char_AddCappedStat(&rec->stats.max_ap, 1);
    if ((a != 0) || (b != 0)) {
        return 0;
    }
    return 4;
}
