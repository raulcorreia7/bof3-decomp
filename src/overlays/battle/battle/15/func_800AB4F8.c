#include "battle_15.h"

/* picks the next frontend cursor id: on a half-or-higher 1-in-8
 * roll (unless the living-player count is 1) it advances the blocked-entry
 * list through func_800AB68C, otherwise it rolls 3..10 through Battle_FindSelectableSlotForward,
 * then stores the chosen id at g_BattleTargetSelector.
 */
MATCH void func_800AB4F8(s32 excluded_id) {
    u8 result;

    if (((rand() & 7) >= 4) && (g_BattleLivingPartyCount != 1)) {
        result = func_800AB68C(excluded_id & BYTE_MASK);
    } else {
        result = Battle_FindSelectableSlotForward((rand() & 7) + 3);
    }
    g_BattleTargetSelector = result;
}
