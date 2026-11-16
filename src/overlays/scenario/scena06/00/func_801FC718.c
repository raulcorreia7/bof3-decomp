#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC718(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(0x2E, 0xF8000, 0x2B0000, 0x80);
            break;
        case 1:
            UI_SetMode(1);
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]      = 3;
                g_SceneState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xF) {
                g_SceneState.step_05 = 4;
                D_80146258 |= 8;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x14) {
                slot                      = Actor_FindFreeSpawned();
                D_1F800000.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                        = 1;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.z = 0xF8;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].layer          = 0x1E;
                    g_SceneState.step_05                                      = 5;
                }
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x18) {
                slot                      = Actor_FindFreeSpawned();
                D_1F800000.cells.bytes[0] = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags                        = 1;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].type           = 0x13;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].camera_angle.z = 0x200;
                    g_SpawnedActors[D_1F800000.cells.bytes[0]].layer          = 0x1E;
                    g_SceneState.step_05                                      = 6;
                }
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x1B) {
                g_SceneState.step_05 = 7;
                Game_RequestAreaChange(0x3C, 0x2F0000, 0x530000, 0x80);
            }
            break;
        case 7:
            g_SceneState.step_05 = 8;
            D_80146258 ^= 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 9) {
                g_SceneState.step_05 = 10;
                SYS_SetFlag(g_SceneFlags, 0x3D);
                Game_RequestAreaChange(0x57, 0x220000, 0x390000, 1);
            }
            break;
        case 9:
            break;
        case 10:
            Game_ClearScriptActive();
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
