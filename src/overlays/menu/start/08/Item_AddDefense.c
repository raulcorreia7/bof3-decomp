#include "start_08.h"

/* func_801E8580 */
MATCH s32 Item_AddDefense(s32 character_index, s32 record_index) {
    Character* rec;
    u8         a;
    u8         b;

    rec = Start_PickPartyRecord(character_index, record_index);
    a   = Char_AddStat(&rec->base.defense, 1);
    b   = Char_AddStat(&rec->stats.defense, 1);
    if ((a != 0) || (b != 0)) {
        return 0;
    }
    return 4;
}
