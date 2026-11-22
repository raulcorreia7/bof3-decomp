#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: camera-actor cuts, the scene messages and the stream that end with scene flags 0xA and 0xB. */
MATCH void func_801F95B8(void) {
    s16 message;

    switch (g_ScenarioState.step_05) {
        case 0:
            D_801FE9D8 = func_8019601C();
            if (D_801FE9D8 != 0xFF) {
                g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                g_SpawnedActors[D_801FE9D8].type           = 0x13;
                g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
                g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x160;
                g_SpawnedActors[D_801FE9D8].layer          = 0x28;
            }
            func_801BE1B0(0);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0xB) {
                message = func_801FD3C0();
                if ((u16)message != 0xFFFF) {
                    SCENARIO_MESSAGE_WAIT(message, 2);
                } else {
                    g_ScenarioState.timer_06 = 0xF;
                    g_ScenarioState.step_05  = 3;
                }
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step_05 = 4;
                g_ScriptVars[0]++;
            }
            break;
        case 3:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step_05 = 4;
                g_ScriptVars[0]++;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0) {
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                    g_SpawnedActors[D_801FE9D8].type           = 0x13;
                    g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FE9D8].layer          = 0x14;
                    g_ScenarioState.step_05                    = 5;
                }
            }
            break;
        case 5:
            if (g_SpawnedActors[D_801FE9D8].header.flags == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0xA);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 10:
            func_801BE1B0(1);
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 0xE) {
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step_05  = 12;
            }
            break;
        case 12:
            if (--g_ScenarioState.timer_06 == 0) {
                func_8019FA28(0x80, TO_COORD(81), TO_COORD(9), 0x82);
                g_GamePrevSelection     = 0x3F;
                g_ScenarioState.step_05 = 13;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 4) {
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                    g_SpawnedActors[D_801FE9D8].type           = 0x13;
                    g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FE9D8].camera_angle.z = 0xF8;
                    g_SpawnedActors[D_801FE9D8].layer          = 0x18;
                    g_ScenarioState.step_05                    = 14;
                }
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 5) {
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                    g_SpawnedActors[D_801FE9D8].type           = 0x13;
                    g_SpawnedActors[D_801FE9D8].camera_angle.x = g_AreaCameraAngle.vx;
                    g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FE9D8].camera_angle.z = 0x200;
                    g_SpawnedActors[D_801FE9D8].layer          = 0x18;
                    g_ScenarioState.step_05                    = 15;
                }
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 9) {
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                    g_SpawnedActors[D_801FE9D8].type           = 0x13;
                    g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x1B8;
                    g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FE9D8].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[D_801FE9D8].layer          = 0x18;
                    g_ScenarioState.step_05                    = 16;
                }
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 0xB) {
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                    g_SpawnedActors[D_801FE9D8].type           = 0x13;
                    g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x2AA;
                    g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FE9D8].camera_angle.z = g_AreaCameraAngle.vz;
                    g_SpawnedActors[D_801FE9D8].layer          = 0x18;
                    g_ScenarioState.step_05                    = 17;
                }
            }
            break;
        case 17:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Item_VitalAdd(9);
                SND_BGMPause(0x3F);
                SND_XAStartStream(2, 1);
                D_80144908[0]           = 0;
                D_80144908[4]           = 0;
                g_ScenarioState.step_05 = 18;
            }
            break;
        case 18:
            if ((u8)SND_XAIsIdle()) {
                SND_BGMResume(0x3F);
                D_801FE9D8 = func_8019601C();
                if (D_801FE9D8 != 0xFF) {
                    g_SpawnedActors[D_801FE9D8].header.flags = 1;
                    g_SpawnedActors[D_801FE9D8].type         = 0x5D;
                    g_SpawnedActors[D_801FE9D8].unk_06       = 0x4E;
                    g_SpawnedActors[D_801FE9D8].unk_07       = 3;
                }
                g_ScenarioState.step_05 = 19;
            }
            break;
        case 19:
            if (g_SpawnedActors[D_801FE9D8].header.flags == 0) {
                g_ScenarioState.step_05 = 20;
            }
            break;
        case 20:
            g_ScenarioState.step_05 = 21;
            g_ScriptVars[0]++;
            break;
        case 21:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                func_801C1E3C(0);
                func_801F9FC4();
                SYS_SetFlag(g_SceneFlags, 0xB);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
    }
}
