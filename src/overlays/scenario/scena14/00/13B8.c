#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801F7FB8(void) {
    switch (g_SceneState.step_05) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            break;
        case 12:
            break;
        case 13:
            break;
        case 14:
            break;
        case 15:
            break;
        case 16:
            break;
        case 17:
            break;
        case 18:
            break;
        case 19:
            break;
        case 20:
            break;
        case 21:
            break;
        case 22:
            break;
        case 23:
            break;
        case 24:
            break;
        case 25:
            break;
        case 26:
            break;
        case 27:
            break;
        case 28:
            break;
        case 29:
            break;
        case 30:
            break;
        case 31:
            break;
        case 32:
            break;
        case 33:
            break;
        case 34:
            break;
        case 35:
            break;
        case 36:
            break;
    }
}
#else
INCLUDE_ASM(func_801F7FB8);
#endif

MATCH void func_801F8800(u8 amount) {
    s32 step;

    step                     = D_801FC44C[g_FrameCount & 0x3] * amount;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY += step;
}

MATCH void func_801F8850(void) {
    u8* flags;

    flags = &D_80145FF4;
    *flags &= 0xFE;
    D_80146134 &= 0xFE;
    Game_RequestAreaChange(AREA_ID_DESERT_MANMO, TO_COORD(41) + COORD_HALF, TO_COORD(22) + COORD_HALF, AREA_ENTRY_MAP_LOADING);
    Game_SetScriptActive();
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
    D_80146871 &= 0xFE;
}
