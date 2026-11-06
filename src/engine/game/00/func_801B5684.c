#include "game_00.h"

MATCH s32 func_801B5684(void) {
    if (g_PartySize >= 2U) {
        if (!((g_GameFlags | g_AreaWalkFlags) & AREA_WALK_ACCEPT_LOCK) && (g_InputPressed & D_80145ABC)) {
            if (func_801B55C0() & 0xFF) {
                g_Task->header.mode = 3;
                g_Task->header.step = 0;
                g_Task->unk_03      = 0;
                g_AreaWalkFlags |= AREA_WALK_STEP_ACTIVE;
                return 1;
            }
        }
    }
    return 0;
}
