#include "battle_15.h"

/* func_800A39B4 */
MATCH void Battle_SetTarget(s16 delta, u8 battler_index) {
    s8* record;
    s8  value;
    s32 total;
    s8  result;

    /* FAKE: volatile-drop cell read. */
    record = *(s8**)&g_Battle.target_record + battler_index;
    value  = record[0x14];
    total  = value + delta;
    if (total >= 51) {
        result = 0x32;
    } else if (total < -25) {
        result = -0x19;
    } else {
        result = (delta + value);
    }
    /* FAKE: statement boundary keeps the retail register order and schedule. */
    FAKE_ORDER_LOCK(record[0x14] = result);
}
