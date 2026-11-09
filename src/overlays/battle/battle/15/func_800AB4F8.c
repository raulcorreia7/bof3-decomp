#include "battle_15.h"

/* picks the next frontend cursor id. */
MATCH void func_800AB4F8(s32 excluded_id) {
    u8 result;

    if ((RANDOM_MASK(7) >= 4) && (g_Battle.living_party_count != 1)) {
        result = func_800AB68C(excluded_id & BYTE_MASK);
    } else {
        result = Battle_TargetNext(RANDOM_MASK(7) + 3);
    }
    g_Battle.target_selector = result;
}
