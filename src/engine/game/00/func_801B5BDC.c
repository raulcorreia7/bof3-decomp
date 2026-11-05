#include "game_00.h"

MATCH void func_801B5BDC(u8 route_index) {
    u32 index;

    if (!(g_GameRequestFlags & 1)) {
        Actor_RequestScript(route_index);
        return;
    }
    index = route_index * 2;
    Actor_RequestScript(s_RouteStepScratch[index]);
    SCRATCH_WORK->unk_2A = s_RouteStepScratch[index + 1];
}
