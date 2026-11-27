#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F70BC(void) {
    u8* entity;

    D_801FAEC0[entity[1]]();
    g_AreaCameraRefreshCount = 2;
}

MATCH s32 func_801F7104(void) {
    s32 mode;

    D_801481F8.x             = 0;
    D_801481F8.y             = 0;
    D_801481F8.z             = 0;
    D_801481E8.x             = g_AreaCameraAngle.vx << 16;
    D_801481E8.y             = g_AreaCameraAngle.vy << 16;
    D_801481E8.z             = g_AreaCameraAngle.vz << 16;
    g_AreaCameraRefreshCount = SELF(Actor)->timer;
    mode                     = 1;
    SELF(Actor)->header.mode = mode;
    return mode;
}

MATCH void func_801F7178(void) {
    u16 angle;
    s16 scroll;

    angle                = (u16)g_AreaCameraAngle.vy;
    scroll               = angle + 244;
    g_AreaCameraAngle.vy = angle + 4;
    Area_ScrollAdvance(scroll);
    if (g_AreaCameraAngle.vy >= 241) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        }
        SELF(Actor)->header.mode = 2;
    }
}

MATCH void func_801F7200(void) {
    u16 angle;
    s16 scroll;

    angle                = (u16)g_AreaCameraAngle.vy;
    scroll               = angle + 236;
    g_AreaCameraAngle.vy = angle - 4;
    Area_ScrollAdvance(scroll);
    if (g_AreaCameraAngle.vy < -240) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
        }
        SELF(Actor)->header.mode = 1;
    }
}

MATCH void func_801F7288(void) {
    SYS_DISPATCH_BYTE(D_801FAEF0, D_80146872);
}

MATCH void func_801F72C4(void) {
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    D_80146872      = 1;
}
