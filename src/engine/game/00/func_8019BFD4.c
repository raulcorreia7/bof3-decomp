#include "game_00.h"

MATCH void func_8019BFD4(void) {
    s32 neg;

    g_AreaCameraStep       = 0x40;
    g_AreaCameraMoving     = 1;
    g_AreaScrollTargetX    = g_Game.members[0].pos.x.fixed;
    g_AreaScrollTargetY    = g_Game.members[0].pos.y.fixed;
    neg                    = -g_AreaCameraHeightStep;
    g_AreaCameraHeightStep = neg;
}
