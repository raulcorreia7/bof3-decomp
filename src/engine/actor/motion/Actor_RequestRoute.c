#include "engine/game/00/game_00.h"

/* func_801B5BDC */
MATCH void Actor_RequestRoute(u8 route_index) {
    u32 index;

    if (!(g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)) {
        Script_Request(route_index);
        return;
    }
    index = route_index * 2;
    Script_Request(s_RouteStepScratch[index]);
    SELF(Actor)->mirror = s_RouteStepScratch[index + 1];
}
