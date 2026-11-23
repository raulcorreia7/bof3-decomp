#include "game_00.h"

MATCH void func_8019BFD4(void) {
    s32 neg;

    g_AreaCameraSpeed           = 0x40;
    g_AreaCameraMoving          = 1;
    g_AreaCamera.scroll_x.fixed = g_Game.members[0].pos.x.fixed;
    g_AreaCamera.scroll_y.fixed = g_Game.members[0].pos.y.fixed;
    neg                         = -g_AreaCameraHeightDelta;
    g_AreaCameraHeightDelta     = neg;
}
