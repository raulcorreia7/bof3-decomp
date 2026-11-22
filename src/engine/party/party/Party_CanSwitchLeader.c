#include "engine/game/00/game_00.h"

/* func_801B55C0 */
MATCH bool Party_CanSwitchLeader(void) {
    s32 count;
    u16 limit;
    s32 index;
    s32 j;

    index = 1;
    if (((g_Game.flags | g_Game.walk_flags) & AREA_WALK_BUSY_ALL) != 0) {
        return false;
    }
    count = g_Game.party_size;
    if (index >= count) {
        return true;
    }
    limit = count;
    do {
        j = 0;
        if (g_Game.members[index].header.mode == 2) {
            for (; j < 3; j++) {
                if (g_Game.members[index].header.step == s_MenuBattlerTypes[j]) {
                    break;
                }
            }
            if (j == 3) {
                return false;
            }
        }
        index++;
    } while (index < limit);
    return true;
}
