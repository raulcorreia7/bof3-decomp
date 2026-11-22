#include "game_00.h"

MATCH s32 func_801B57F8(void) {
    u32 mode;

    if (((g_Game.flags | g_Game.walk_flags) & AREA_WALK_BUSY_ALL) != 0) {
        return 0;
    }
    mode = g_Game.party_size;
    if (mode <= 1u || (g_Game.members[1].header.mode != 1 && g_Game.members[1].header.mode != 6) || mode != 3 || g_Game.members[2].header.mode == 1 || g_Game.members[2].header.mode == 6) {
        return 1;
    }
    return 0;
}
