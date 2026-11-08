#include "battle_15.h"

/* picks the next frontend cursor id: on a half-or-higher 1-in-8
 * roll (unless the living-player count is 1) it advances the blocked-entry
 * list through func_800AB68C, otherwise it rolls 3..10 through Battle_FindNextTarget,
 * then stores the chosen id at g_Battle.target_selector.
 */
MATCH void func_800AB4F8(s32 excluded_id) {
    u8 result;

    if ((RANDOM_MASK(7) >= 4) && (g_Battle.living_party_count != 1)) {
        result = func_800AB68C(excluded_id & BYTE_MASK);
    } else {
        result = Battle_FindNextTarget(RANDOM_MASK(7) + 3);
    }
    g_Battle.target_selector = result;
}
