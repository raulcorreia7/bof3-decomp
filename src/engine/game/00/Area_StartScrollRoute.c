#include "game_00.h"

/* func_801C601C */
MATCH void Area_StartScrollRoute(s8 route_index) {
    s32 first;
    s16 dist;

    func_801BE710((GameResetRecord*)&D_80143FBC);
    first      = g_AreaScrollTargetX;
    D_80143FC0 = 3;
    D_80143FBF = route_index;
    D_80143FC1 |= 0x80;
    g_PartyX       = MEM(s32, 0x80149308u);
    g_PartyY       = g_AreaScrollTargetY;
    dist           = Area_SampleHeight(first, MEM(s32, 0x8014930Cu));
    g_ScrollHeight = dist;
    Area_AdvanceScroll(dist);
    D_80143F49 = 1;
    D_80143F4A = 0;
    D_80143F4B = 0;
}
