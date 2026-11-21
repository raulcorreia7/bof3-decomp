#include "game_00.h"

/* D_80195ED4 */
AreaActionSteps g_AreaActionSteps = {
    AreaAction_RollStep, AreaAction_FindSmall, AreaAction_FindLarge, AreaAction_End, AreaAction_WaitMessage,
};

static u8 s_gap_80195EE8[4] = {0};
