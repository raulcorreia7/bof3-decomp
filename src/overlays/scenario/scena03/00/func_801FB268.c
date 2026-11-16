#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FB268(void) {
    u8 slot;
    s8 staged;

    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_SceneState.timer_06 != 0) {
                g_SceneState.timer_06--;
                break;
            }
            g_ScriptVars[0] = 0;
            Scene_SetupParty(4);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 2) {
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            Game_RequestAreaChange(0x63, 0x68000, 0x230000, 1);
            g_GameRequestKind    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_SceneState.step_05 = 3;
            break;
        case 3:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 4;
            break;
        case 4:
            if (g_ScriptVars[0] == 7) {
                Game_RequestAreaChange(0x63, 0x230000, 0x510000, 0x85);
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x12) {
                slot            = Actor_FindFreeSpawned();
                g_ScratchPad[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags              = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[g_ScratchPad[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.x = -0x32E;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad[0]].layer          = 0x38;
                }
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x16) {
                staged              = Actor_FindFreeSpawned();
                g_SceneState.unk_03 = staged;
                if (staged != -1) {
                    g_SpawnedActors[staged].header.flags                  = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[LOB(g_SceneState.unk_03)].type        = 0x22;
                    g_SpawnedActors[LOB(g_SceneState.unk_03)].pos.x.fixed = 0x230000;
                    g_SpawnedActors[LOB(g_SceneState.unk_03)].pos.y.fixed = 0x4F0000;
                    g_SpawnedActors[LOB(g_SceneState.unk_03)].pos.z.fixed = TO_COORD(0x480);
                }
                g_SceneState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x18) {
                slot            = Actor_FindFreeSpawned();
                g_ScratchPad[0] = slot;
                if (slot != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags              = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[g_ScratchPad[0]].type           = 0x13;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.x = -0x2AA;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[g_ScratchPad[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[g_ScratchPad[0]].layer          = 0x38;
                }
                g_SceneState.step_05 = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x27) {
                g_AreaDrawFlags      = 0;
                g_SceneState.step_05 = 9;
            }
            break;
        case 9:
            g_SceneState.timer_06 = 0xA;
            g_SceneState.step_05  = 0xA;
            g_ScriptVars[0]++;
            break;
        case 10:
            if (g_SceneState.timer_06 != 0) {
                g_SceneState.timer_06--;
                break;
            }
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 0xB;
            g_ScriptVars[0]++;
            break;
        case 11:
            if (g_ScriptVars[0] == 0x2F) {
                g_SceneState.step_05 = 0xC;
            }
            break;
        case 12:
            g_SceneState.step_05 = 0xD;
            break;
        case 13:
            if (g_ScriptVars[0] == 0x34) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x1D);
                g_ScriptVars[0]       = 0;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
                D_80146258 &= ~0x80;
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801FB268);
#endif
