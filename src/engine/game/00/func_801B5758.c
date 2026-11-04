#include "game_00.h"

MATCH s32 func_801B5758(void) {
    if (g_InputPressed & D_80145AB8) {
        if (!(g_GameFlags & GAME_FLAG_RUN_LOCK)) {
            SND_PlayCue(EMI_CUE_ID(1, 5));
            g_AreaWalkFlags |= AREA_WALK_RUN_ACTIVE;
            func_801B5BDC(g_SpadWork->direction_08);
            g_SpadWork->unk_01   = 4;
            g_SpadWork->state_02 = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
