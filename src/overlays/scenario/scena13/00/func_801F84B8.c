#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F84B8(void) {
    switch (g_ScenarioState.step) {
        case 0:
            D_801FBFEC = func_8019601C();
            if (D_801FBFEC != 0xFF) {
                g_SpawnedActors[D_801FBFEC].header.flags   = 1;
                g_SpawnedActors[D_801FBFEC].type           = 0x13;
                g_SpawnedActors[D_801FBFEC].camera_angle.x = -0x2AA;
                g_SpawnedActors[D_801FBFEC].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FBFEC].camera_angle.z = 0x200;
                g_SpawnedActors[D_801FBFEC].layer          = 0x80;
                g_ScenarioState.step                       = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 8) {
                UI_ModeSet(0);
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags = 0;
                SYS_ThreadWait(1);
                g_GameStateIndex     = 6;
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0] = 0;
                SYS_SetFlag(g_SceneFlags, 0);
                func_8019FA28(0x7E, 0x4E0000, 0x2C8000, 1);
                g_GameRequestType    = 0xFF;
                g_GameEntryMode      = 0xFF;
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (g_GameStateIndex == 0) {
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_SysThreads[2].state == 0) {
                g_GameFlags &= 0xFFF7;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
