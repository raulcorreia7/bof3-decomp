#include "game_00.h"

/* func_801C5DFC */
MATCH void Area_SetFacingOffsetX(u8 route_index) {
    s16 step;
    s32 scale;
    s32 x;
    s32 y;

    if ((route_index == 2) || (route_index == 6)) {
        g_AreaCameraStep = 4;
    } else {
        g_AreaCameraStep = 8;
    }
    /* The retail build reloads the step table at each use: a non-const view
     * keeps the three reads separate. */
    step             = g_AreaCameraStep * ((u8*)g_RouteSpeedScale)[D_80143FC0];
    scale            = 0x80 / step;
    g_AreaCameraStep = step;
    x                = g_PartyX + g_FacingOffsets[route_index].x * ((u8*)g_RouteSpeedScale)[D_80143FC0] * scale * D_80143FC3;
    /* FAKE: a const view lets the scheduler hoist the y table load above the x
     * store; the retail build keeps it after. */
    FAKE_ORDER_LOCK(g_PartyX = x);
    y                      = g_PartyY + g_FacingOffsets[route_index].y * ((u8*)g_RouteSpeedScale)[D_80143FC0] * scale * D_80143FC3;
    g_AreaScrollTargetX    = x;
    g_PartyY               = y;
    g_AreaScrollTargetY    = y;
    D_80143F5C             = ((Area_SampleHeight(g_PartyX, g_PartyY) - g_ScrollHeight) << 16) / ((0x80 / g_AreaCameraStep) * D_80143FC3);
    g_AreaCameraHeightStep = 0;
}
