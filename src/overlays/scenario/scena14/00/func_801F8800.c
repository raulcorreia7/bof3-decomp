#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
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
    g_ScenarioState.state_04 = 2;
    g_ScenarioState.step_05  = 0;
    D_80146871 &= 0xFE;
}
