#include "battle_15.h"

MATCH s32 func_800A7B40(u8 combination, u8 count) {
    u8* rec;
    u8  limit;
    u8  i;

    rec   = D_80145F04 + g_Battle.active_battler * BATTLE_PARTY_STRIDE;
    limit = count;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        u8 j;

        if (D_800B4EB0[combination][i] == 0) {
            return limit;
        }
        for (j = 0; j < limit; j++) {
            if (*(rec + j + 0x70) == D_800B4EB0[combination][i]) {
                /* id already listed. */
                goto next;
            }
        }
        if (limit == 9) {
            return limit;
        }
        *(rec + limit + 0x70) = D_800B4EB0[combination][i];
        limit++;
    next:;
    }
    return limit;
}
