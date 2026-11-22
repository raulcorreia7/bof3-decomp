#include "engine/game/00/game_00.h"

/* func_801C601C */
MATCH void Area_ScrollStartRoute(s8 route_index) {
    s32 first;
    s16 dist;

    func_801BE710((GameReset*)&D_80143FBC);
    first      = g_AreaScrollTargetX;
    D_80143FC0 = 3;
    D_80143FBF = route_index;
    D_80143FC1 |= 0x80;
    g_PartyPos.x.fixed      = MEM(s32, 0x80149308u);
    g_PartyPos.y.fixed      = g_AreaScrollTargetY;
    dist                    = Area_HeightSample(first, MEM(s32, 0x8014930Cu));
    COORD_INT(g_PartyPos.z) = dist;
    Area_ScrollAdvance(dist);
    D_80143F49 = 1;
    D_80143F4A = 0;
    D_80143F4B = 0;
}
