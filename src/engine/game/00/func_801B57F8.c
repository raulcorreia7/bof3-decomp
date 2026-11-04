#include "game_00.h"

MATCH s32 func_801B57F8(void) {
    u32 mode;

    if (((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_BUSY_ALL) != 0) {
        return 0;
    }
    mode = g_PartySize;
    if (mode <= 1u || (D_80145FD1 != 1 && D_80145FD1 != 6) || mode != 3 || D_80146111 == 1 || D_80146111 == 6) {
        return 1;
    }
    return 0;
}
