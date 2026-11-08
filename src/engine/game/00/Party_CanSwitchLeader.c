#include "game_00.h"

/* func_801B55C0 */
MATCH bool Party_CanSwitchLeader(void) {
    s32 count;
    u16 limit;
    s32 index;
    s32 j;
    s32 offset;

    s32 key_offset;
    index = 1;
    if (((g_Game.flags | g_Game.walk_flags) & AREA_WALK_BUSY_ALL) != 0) {
        return false;
    }
    count = g_Game.party_size;
    if (index >= count) {
        return true;
    }
    limit  = count;
    offset = BATTLE_PARTY_STRIDE;
    do {
        j = 0;
        if (D_80145E91[offset] == 2) {
            key_offset = offset;
            for (; j < 3; j++) {
                if (D_80145E92[key_offset] == s_MenuBattlerKinds[j]) {
                    break;
                }
            }
            if (j == 3) {
                return false;
            }
        }
        index++;
        offset += BATTLE_PARTY_STRIDE;
    } while (index < limit);
    return true;
}
